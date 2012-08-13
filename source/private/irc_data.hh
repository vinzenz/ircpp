//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

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

