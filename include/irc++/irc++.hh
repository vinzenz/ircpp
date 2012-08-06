// vim:set ts=8 sw=4 tw=0 et:
#ifndef GUARD_IRCPP_IRCPP_HH_INCLUDED
#define GUARD_IRCPP_IRCPP_HH_INCLUDED

#include <cstdint>
#include <string>
#include <memory>
#include <functional>

namespace ircpp {

typedef std::function<void()> handler_t;

class irc {
    struct implementation;
    std::shared_ptr<implementation> impl_;
public:
    irc();

    void connect( 
        std::string const & server,
        std::string const & port, 
        std::string const & nick, 
        std::string const & user,
        std::string const & host,
        std::string const & realname );

    void handle(
        std::string const & command,
        handler_t handler );

    void run();

private: // Not copyable
    irc(irc const &);
    irc & operator=(irc const &);
};

}

#endif //GUARD_IRCPP_IRCPP_HH_INCLUDED

