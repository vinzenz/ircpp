#ifndef GUARD_IRCPP_PRIVATE_CONNECTION_IMPL_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_CONNECTION_IMPL_HH_INCLUDED

#include <irc++/connection.hh>
#include "instance_data.hh"

namespace ircpp {
namespace detail {

class connection_impl : public ircpp::connection {
    instance_data instance_;
public:
    connection_impl( instance_data instance );
    virtual ~connection_impl();
    
    virtual void send_raw(
        std::string const & raw_message );

    virtual void send(
        std::string const & target,
        std::string const & command,
        std::vector<std::string> const & args );
};

}}

#endif //GUARD_IRCPP_PRIVATE_CONNECTION_IMPL_HH_INCLUDED