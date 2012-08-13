//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_INSTANCE_INFO_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_INSTANCE_INFO_HH_INCLUDED

#include "connection_info.hh"
#include "user_info.hh"
#include "statistics.hh"
#include "user_mod_info.hh"
#include "channel_info.hh"

namespace ircpp {
namespace detail {

struct instance_info {
    instance_info()
    : connection()
    , user()
    , stats()
    , user_mods()
    , channels()
    {
    }

    connection_info connection;
    user_info       user;
    statistics      stats;
    user_mod_info   user_mods;
    channels_info   channels;
};

}}

#endif //GUARD_IRCPP_PRIVATE_INSTANCE_INFO_HH_INCLUDED
