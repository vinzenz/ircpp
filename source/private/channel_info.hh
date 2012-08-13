//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

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
