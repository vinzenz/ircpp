//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_IRCPP_HH_INCLUDED
#define GUARD_IRCPP_IRCPP_HH_INCLUDED

#include <irc++/handler_base.hh>

#include <string>
#include <memory>

namespace ircpp {

class irc {
    struct implementation;
    std::shared_ptr<implementation> impl_;
public:
    irc();

    bool connect(
        std::string const & server,
        std::string const & port,
        std::string const & nick,
        std::string const & user,
        std::string const & host,
        std::string const & realname,
        std::shared_ptr<handler_base_t> handler );

    void run();

private: // Not copyable
    irc(irc const &);
    irc & operator=(irc const &);
};

}

#endif //GUARD_IRCPP_IRCPP_HH_INCLUDED

#ifndef GUARD_IRCPP_IRCPP_HH_INCLUDED
#define GUARD_IRCPP_IRCPP_HH_INCLUDED

#include <irc++/handler_base.hh>

#include <string>
#include <memory>

namespace ircpp {

class irc {
    struct implementation;
    std::shared_ptr<implementation> impl_;
public:
    irc();

    bool connect(
        std::string const & server,
        std::string const & port,
        std::string const & nick,
        std::string const & user,
        std::string const & host,
        std::string const & realname,
        std::shared_ptr<handler_base_t> handler );

    void run();

private: // Not copyable
    irc(irc const &);
    irc & operator=(irc const &);
};

}

#endif //GUARD_IRCPP_IRCPP_HH_INCLUDED

