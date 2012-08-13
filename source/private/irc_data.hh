#ifndef GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED

#include <ostream>
#include <boost/asio.hpp>

namespace ircpp {
namespace detail {

using boost::asio::ip::tcp;

struct irc_data {
    irc_data()
    : io()
    , resolver( io )
    {}

    boost::asio::io_service     io;
    tcp::resolver               resolver;
};

}}

#endif //GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED

