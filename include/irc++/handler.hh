//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_HANDLER_HH_INCLUDED
#define GUARD_IRCPP_HANDLER_HH_INCLUDED

#include <irc++/handler_base.hh>
#include <irc++/log_severity.hh>

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace ircpp {
struct handler_t : handler_base_t {
    virtual void on_error( std::string const & /*reason*/ )
    {}

    virtual void on_connected( connection & /*conn*/)
    {}

    virtual void on_disconnected()
    {}

    virtual void on_log_message(
        log_severity_t severity,
        std::string const & source,
        std::string const & message )
    {
        std::string sev;
        switch( severity ) {
            case log_debug:
                sev = "DEBUG";
                break;
            case log_info:
                sev = "INFO";
                break;
            case log_warn:
                sev = "WARNING";
                break;
            case log_error:
                sev = "ERROR";
                break;
            default:
                assert("unknown severity");
                sev = "UNKNOWN";
                break;
        }
        std::cout << sev << ": FUN(" << source << ") MSG: " << message << std::endl;
    }

    virtual void on_command(
        connection & /*conn*/,
        std::string const & /*sender*/,
        std::string const & /*command*/,
        std::vector<std::string> const & /*arguments*/ )
    {}
};

}

#endif //GUARD_IRCPP_HANDLER_HH_INCLUDED
