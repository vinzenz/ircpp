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
