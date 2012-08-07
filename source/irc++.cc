#include <irc++/irc++.hh>
#include <boost/bind.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <list>

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
    detail::instance_data instance( impl_->data, *impl_->connections.back() );
    instance.info().connection.server   = server;
    instance.info().connection.port     = port;
    instance.info().user.nick           = nick;
    instance.info().user.host           = host;
    instance.info().user.user           = user;
    instance.info().user.real           = realname;

    // Preforming resolve
    tcp::resolver::query query( server, port );
    impl_->data.resolver.async_resolve(
        query,
        [instance](
            boost::system::error_code const & ec,
            tcp::resolver::iterator it) {
                instance.log() << "Resolved host" << std::endl;
                handle_resolve( 
                    instance,
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
