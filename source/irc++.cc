#include <irc++/irc++.hh>
#include <boost/bind.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/format.hpp>
#include <iostream>

#include "private/handlers.hh"

namespace ircpp {

using boost::asio::ip::tcp;
namespace bap = boost::asio::placeholders;
using namespace ircpp::detail;

struct irc::implementation {
    implementation( std::ostream & logstream )
    : data( logstream )
    , connections()
    {}

    irc_data data;
    std::list<conn_ptr> connections;
};

irc::irc()
: impl_( std::make_shared< irc::implementation >(std::cout) )
{}

void irc::connect( 
    std::string const & server,
    std::string const & port, 
    std::string const & nick, 
    std::string const & user,
    std::string const & host,
    std::string const & realname )
{
    // New conn instance
    impl_->connections.push_back( std::make_shared<connection_data>(impl_->data) );

    // Using data
    connection_data & data  = *impl_->connections.back();
    data.details.server     = server;
    data.details.port       = port;
    data.details.nick       = nick;
    data.details.host       = host;
    data.details.user       = user;
    data.details.realname   = realname;
    
    // Preforming resolve
    tcp::resolver::query query( server, port );
    impl_->data.resolver.async_resolve(
        query,
        [&]( 
            boost::system::error_code const & ec,
            tcp::resolver::iterator it) {
                impl_->data.logstream << "Resolved host" << std::endl;
                handle_resolve( 
                    detail::instance_data( impl_->data, data ),
                    it,
                    ec
                );
        }
    );
}

void irc::handle(
    std::string const & command,
    handler_t handler )
{

}

void irc::run()
{
    impl_->data.io.run();
}

}
