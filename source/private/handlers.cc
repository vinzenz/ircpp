#include "handlers.hh"
#include "parser.hh"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <cassert>
#include <sstream>

namespace ircpp {
namespace detail {

/**
 * @brief sends a 'line/message' to the server
 * @param instance shared instance data
 * @param line the line/message to be sent
 */
void send_line( 
    instance_data instance,
    std::string line )
{
    instance.log_info( "send_line", "MESSAGE SENT: " + line );
    line += "\r\n";
    boost::asio::async_write(
        instance.conn().socket,
        boost::asio::buffer(line),
        [instance]( 
            boost::system::error_code const & ec,
            std::size_t written )
        {
            instance_data data = instance_data(instance);
            data.info().stats.bytes_transferred.written += written;
            data.info().stats.messages.sent += 1;
        }
    );
}

/**
 * @brief Parses a message and relays it to the message dispatcher
 * @param instance shared instance data
 * @param line message to be parsed
 */
void parse_line( instance_data instance, std::string const & line )
{
    instance.log_debug( "parse_line", "MESSAGE RECEIVED: " + line );
    message_data data;
    if( parse_message( line, data ) )
    {
        if( data.command == "PING" )
        {
            std::string reply = "PONG";
            if( !data.arguments.empty() )
            {
                reply += " " + data.arguments.back();
            }
            send_line( instance, reply );
        }
    }
    else 
    {
        instance.log_error( "parse_line", "PARSER ERROR ON MESSAGE: " + line );
    }
}

/**
 * @brief Retrieves last read line from the readbuffer and passes it over to parse_line, it will trim trailing '\r' and '\n' characters.
 * @param instance
 */
void handle_line_read( 
    instance_data instance )
{
    std::istream is( instance.conn().readbuffer.get() );
    std::string line;
    if( std::getline( is, line ) )
    {
        boost::algorithm::trim_right_if( line, boost::algorithm::is_any_of("\r\n") );
        parse_line( instance, line );
    }
}

/**
 * @brief Reads one message from the socket and passes it over to the handle_line_read. In case of a failure it will stop reading from the socket, otherwise it will schedule the next read
 * @param instance
 */
void read_next( 
    instance_data instance )
{
    boost::asio::async_read_until(
        instance.conn().socket,
        *instance.conn().readbuffer,
        "\n",
        [instance](
            boost::system::error_code const & ec,
            size_t read )
        {
            instance_data data(instance);
            if( !ec )
            {
                data.info().stats.bytes_transferred.read += read;
                data.info().stats.messages.received += 1;
                
                handle_line_read( instance );
                read_next( instance );            
            }
            else
            {
                instance.log_error( "next_read", "read failure: " + ec.message() );
            }
        }        
    );
}

/**
 * @brief Kicks of the message handling loop
 * @param instance shared instance data
 */
void start_reader_loop( 
    instance_data instance )
{
    read_next( instance );
}

/**
 * @brief Implementation of login handling
 * @param instance shared instance data
 */
void perform_login( 
    instance_data instance )
{
    if( !instance.info().user.pass.empty() )
    {
        send_line( instance, "PASS " + instance.info().user.pass );
    }
    send_line( instance, "NICK " + instance.info().user.nick );
    send_line( instance, 
        "USER " + instance.info().user.user + " 0 * :" + instance.info().user.real
    );
}

/**
 * @brief handles successful connection attempts. It starts the message handling loop and kicks off the login
 * @param instance shared instance data
 */
void handle_connected( 
    instance_data instance )
{
    start_reader_loop( instance );
    perform_login( instance );
}


/**
 * @brief handles the established or failed connect event, in case of failure it tries to attempt to connect to the next resolved endpoint
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param endpoint last tried endpoint
 * @param err result of connect attempt
 */
void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err ) 
{
    if( !err )
    {
        std::ostringstream eps;
        eps << endpoint;
        instance.log_info( "handle_connect", "Connected to: " + eps.str() );
        instance.info().connection.endpoint = endpoint;
        instance.irc().io.post(
            [instance]()
            {
                handle_connected( instance );
            }
        );
    }    
    else if( !next_connect( instance, endpoint_iterator ) )
    {
        instance.log_error( "handle_connect", "Error during connecting: " + err.message() );
    }
}

/**
 * @brief schedules an asynchronous connect to the resolved host, if applicable
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @return returns true if a connect attempt has been scheduled. It returns false if no endpoints have been resolved or none has been resolved at all 
 */
bool next_connect(
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator )
{
    if( endpoint_iterator != tcp::resolver::iterator() )
    {
        // Retrieving endpoint
        tcp::endpoint ep = *endpoint_iterator;
        
        std::ostringstream eps;
        eps << ep;
        instance.log_info( "next_connect", "Endpoint resolved. Attempting to connect to: " + eps.str() );

        // Stepping iterator for next connection
        endpoint_iterator++;
        
        // Schedule connect
        instance.conn().socket.async_connect(
            ep,
            [instance, ep, endpoint_iterator]( // Capture all values by copy
                boost::system::error_code const & ec )
            {
                // Handle connect attempt result
                handle_connect(
                    instance,
                    endpoint_iterator,
                    ep,
                    ec
                );
            }
        );
        // Scheduled connect
        return true;
    }
    // Failed to schedule connect -> No more endpoints available
    return false;
}

/**
 * @brief handle_resolve handles the result of resolving the server host
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param err result of resolving host
 */
void handle_resolve( 
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator,
    boost::system::error_code const &   err )
{    
    // Successful and iterator not at the end
    if( !err && endpoint_iterator != tcp::resolver::iterator() )
    {
        // Perform connect
        next_connect( instance, endpoint_iterator );
    }
    // An error occurred during resolving the hostname
    else if ( err )
    {
        instance.log_error( "handle_resolve", "An error occurred during resolving host: " + err.message() );
    }
    // iterator at the end
    else if( endpoint_iterator == tcp::resolver::iterator() )
    {
        instance.log_error( "handle_resolve", "Host " +  instance.info().connection.server + " couldn't be resolved" );
    }
    else
    {
        // WTF?
        assert(false && "If this happens something is pretty fishy.");
    }
}

}}

