//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED

#include <string>

namespace ircpp {
namespace detail {

struct user_info {
    user_info()
    : nick()
    , user()
    , host()
    , real()
    , pass()
    {
    }

    std::string nick;
    std::string user;
    std::string host;
    std::string real;
    std::string pass;
};

}}

#endif //GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED
#ifndef GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED

#include <string>

namespace ircpp {
namespace detail {

struct user_info {
    user_info()
    : nick()
    , user()
    , host()
    , real()
    , pass()
    {
    }

    std::string nick;
    std::string user;
    std::string host;
    std::string real;
    std::string pass;
};

}}

#endif //GUARD_IRCPP_PRIVATE_USER_INFO_HH_INCLUDED
