//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_CONNECTION_INFO_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_CONNECTION_INFO_HH_INCLUDED

#include <string>
#include <boost/asio/ip/tcp.hpp>

namespace ircpp {
namespace detail {

struct connection_info {
    connection_info()
    : endpoint()
    , server()
    , port()
    {
    }

    boost::asio::ip::tcp::endpoint endpoint;
    std::string server;
    std::string port;
};

}}

#endif //GUARD_IRCPP_PRIVATE_CONNECTION_INFO_HH_INCLUDED
