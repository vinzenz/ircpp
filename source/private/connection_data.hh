//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_CONNECTION_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_CONNECTION_DATA_HH_INCLUDED

#include "irc_data.hh"
#include "server_data.hh"

#include <memory>

namespace ircpp {
namespace detail {

struct connection_data {
    connection_data( irc_data & irc_ )
    : irc( irc_ )
    , socket( irc.io )
    , readbuffer( std::make_shared< boost::asio::streambuf >() )
    {}

    irc_data  & irc;
    tcp::socket socket;
    std::shared_ptr< boost::asio::streambuf > readbuffer;
};

typedef std::shared_ptr<connection_data> conn_ptr;

}}

#endif // GUARD_IRCPP_PRIVATE_CONNECTION_DATA_HH_INCLUDED

