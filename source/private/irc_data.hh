#ifndef GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED

#include <ostream>
#include <boost/asio.hpp>

namespace ircpp {
namespace detail {

using boost::asio::ip::tcp;

struct irc_data {
    irc_data( std::ostream & oslog )
    : io()
    , resolver( io )
    , logstream( oslog )
    {}

    boost::asio::io_service     io;
    tcp::resolver               resolver;
    std::ostream              & logstream;
};

}}

#endif //GUARD_IRCPP_PRIVATE_IRC_DATA_HH_INCLUDED

