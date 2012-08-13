#ifndef GUARD_IRCPP_HANDLER_BASE_HH_INCLUDED
#define GUARD_IRCPP_HANDLER_BASE_HH_INCLUDED

#include <irc++/log_severity.hh>
#include <irc++/connection.hh>

#include <string>
#include <vector>

namespace ircpp {

struct handler_base_t {
    virtual ~handler_base_t(){}
    virtual void on_error( std::string const & reason ) = 0;

    virtual void on_connected( connection & ) = 0;

    virtual void on_disconnected() = 0;

    virtual void on_log_message(
        log_severity_t severity,
        std::string const & source,
        std::string const & message ) = 0;

    virtual void on_command(
        connection & conn,
        std::string const & sender,
        std::string const & command,
        std::vector<std::string> const & arguments ) = 0;
};


}

#endif //GUARD_IRCPP_HANDLER_BASE_HH_INCLUDED
