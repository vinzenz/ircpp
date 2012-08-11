// vim:set ts=8 sw=4 tw=0 et:
#ifndef GUARD_IRCPP_IRCPP_HH_INCLUDED
#define GUARD_IRCPP_IRCPP_HH_INCLUDED

#include <cstdint>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <iostream>
#include <cassert>

namespace ircpp {

enum log_severity_t {
        log_debug   = 0,
        log_info    = 1,
        log_warn    = 2,
        log_error   = 3
};

struct connection {
    virtual ~connection(){}

    virtual void send_raw(
        std::string const & raw_message ) = 0;

    virtual void send(
        std::string const & target,
        std::string const & command,
        std::vector<std::string> const & args ) = 0;
};

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

