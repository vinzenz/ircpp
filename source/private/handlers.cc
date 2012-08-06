#include "handlers.hh"
#include <boost/format.hpp>

namespace ircpp {
namespace detail {

void send_message(
    instance_data   instance,
    std::string const & message )
{

    instance.irc().logstream << "Sending message: " << message << std::endl;
    boost::asio::async_write(
        instance.conn().socket,
        boost::asio::buffer(message),
        [instance]( boost::system::error_code const & ec, size_t written ) {
            if( !ec ) {
                next_read( instance );
            }
            else {
                instance.irc().logstream << "Sending login data failed: " << ec.message() << std::endl;
            }
        }
    );

}

void handle_message(
    instance_data                       instance,
    boost::system::error_code const &   ec,
    size_t                              bytes_read )
{
    if( !ec )
    {
        std::istream is( instance.conn().readbuffer.get() );
        std::string line;
        std::getline( is, line );
        instance.irc().logstream << "Message received: " << line << std::endl;
        if( line.substr(0,4) == "PING" ) {
            line.erase(5,1);
            line[1] = 'O';
            line += "\r\n";
            send_message( instance, line );
        }
        else {
            next_read( instance );
        }
    }
    else
    {
        instance.irc().logstream << "Read failed: " << ec.message() << std::endl;
    }
}

void next_read(
    instance_data   instance )
{

    boost::asio::async_read_until(
        instance.conn().socket,
        *instance.conn().readbuffer,
        "\n",
        [instance](
            boost::system::error_code const & ec,
            size_t read )
        {
            handle_message( instance, ec, read );
        }
    );
}

void handle_connected(
    instance_data       instance )
{
    instance.irc().logstream << "Starting login..." << std::endl;
    boost::format fmt("NICK %1%\r\nUSER %2% %3% * :%4%\r\n");
    fmt % instance.conn().details.nick
        % instance.conn().details.user
        % instance.conn().details.host
        % instance.conn().details.realname;    
    instance.irc().logstream << "SENDING: " << fmt.str() << std::endl;
    send_message(instance, fmt.str());
}


void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err ) 
{
    if( !err ) {
        instance.irc().logstream << "Connected to: " << endpoint << std::endl;
        instance.conn().details.endpoint = endpoint;
        instance.irc().io.post(
            [instance]()
            {
                handle_connected( instance );
            }
        );
    }    
    else if( !next_connect( instance, endpoint_iterator ) ) {
        instance.irc().logstream << "Error during connecting: " << err.message() << std::endl;
    }
}

bool next_connect(
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator )
{
    instance.irc().logstream << "Resolving host for: " << instance.conn().details.server << std::endl;
    if( endpoint_iterator != tcp::resolver::iterator() ) { 
        tcp::endpoint ep = *endpoint_iterator;
        endpoint_iterator++;
        instance.conn().socket.async_connect(
            ep,
            [instance, ep, endpoint_iterator]( // Capture all values by copy
                boost::system::error_code const & ec ) {
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
    if( !err ) {
        instance.irc().logstream << "Handling resolved endpoint" << std::endl;
        next_connect( instance, endpoint_iterator );
    }
    else {
        instance.irc().logstream << "An error occurred: " << err.message() << std::endl;
    }
}

}}

