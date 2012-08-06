#ifndef GUARD_IRCPP_PRIVATE_SERVER_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_SERVER_DATA_HH_INCLUDED

#include <string>
#include <boost/asio.hpp>

namespace ircpp {
namespace detail {

using boost::asio::ip::tcp;

struct server_data {
    std::string     server;
    std::string     port;
    std::string     nick;
    std::string     user;
    std::string     host;
    std::string     realname;   
    tcp::endpoint   endpoint;
};

}}
#endif // GUARD_IRCPP_PRIVATE_SERVER_DATA_HH_INCLUDED
