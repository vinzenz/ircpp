#ifndef GUARD_IRCPP_PRIVATE_CHANNEL_INFO_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_CHANNEL_INFO_HH_INCLUDED

namespace ircpp {
namespace detail {

struct channel_info {
    channel_info()
    : name()
    , active(false)
    , topic()
    , modes()
    , names()
    {}

    std::string name;
    bool active;
    std::string topic;
    std::string modes;
    std::vector<std::string> names;
};

struct channels_info {
    channels_info()
    : history()
    {}

    std::vector<channel_info> history;
};

}}

#endif //GUARD_IRCPP_PRIVATE_CHANNEL_INFO_HH_INCLUDED
