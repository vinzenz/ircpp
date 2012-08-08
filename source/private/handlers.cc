#include "handlers.hh"
#include "parser.hh"

namespace ircpp {
namespace detail {

void send_line( 
    instance_data instance,
    std::string line )
{
    instance.log() << "MESSAGE SENT: " << line << std::endl;                
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

void parse_line( instance_data instance, std::string const & line )
{
    instance.log() << "MESSAGE RECEIVED: " << line << std::endl;
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
        instance.log() << "PARSER ERROR ON MESSAGE: " << line << std::endl;
    }
}

void handle_line_read( 
    instance_data instance )
{
    std::istream is( instance.conn().readbuffer.get() );
    std::string line;
    if( std::getline( is, line ) )
    {
        parse_line( instance, line );
    }
}

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
                instance.log() << "read failure: " << ec.message() << std::endl;                
            }
        }        
    );
}

void start_reader_loop( 
    instance_data instance )
{
    read_next( instance );
}

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

void handle_connected( 
    instance_data instance )
{
    start_reader_loop( instance );
    perform_login( instance );
}

void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err ) 
{
    if( !err )
    {
        instance.log() << "Connected to: " << endpoint << std::endl;
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
        instance.log() << "Error during connecting: " << err.message() << std::endl;
    }
}

bool next_connect(
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator )
{
    instance.log() << "Resolving host for: " << instance.info().connection.server << std::endl;
    if( endpoint_iterator != tcp::resolver::iterator() )
    {
        tcp::endpoint ep = *endpoint_iterator;
        endpoint_iterator++;
        instance.conn().socket.async_connect(
            ep,
            [instance, ep, endpoint_iterator]( // Capture all values by copy
                boost::system::error_code const & ec )
            {
                handle_connect(
                    instance,
                    endpoint_iterator,
                    ep,
                    ec
                );
            }
        );
        return true;
    }
    return false;
}

void handle_resolve( 
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator,
    boost::system::error_code const &   err )
{    
    if( !err )
    {
        instance.log() << "Handling resolved endpoint" << std::endl;
        next_connect( instance, endpoint_iterator );
    }
    else
    {
        instance.log() << "An error occurred during resolving host: " << err.message() << std::endl;
    }
}

}}

