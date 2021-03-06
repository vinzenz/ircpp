//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_CONNECTION_HH_INCLUDED
#define GUARD_IRCPP_CONNECTION_HH_INCLUDED

#include <string>
#include <vector>

namespace ircpp {

struct connection {
    virtual ~connection(){}

    virtual void send_raw(
        std::string const & raw_message ) = 0;

    virtual void send(
        std::string const & target,
        std::string const & command,
        std::vector<std::string> const & args ) = 0;
};

}

#endif //GUARD_IRCPP_CONNECTION_HH_INCLUDED
