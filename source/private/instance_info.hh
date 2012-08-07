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
    connection_info connection;
    user_info       user;
    statistics      stats;
    user_mod_info   user_mods;
    channels_info   channels;
};

}}

#endif //GUARD_IRCPP_PRIVATE_INSTANCE_INFO_HH_INCLUDED
