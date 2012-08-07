#ifndef GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED

#include "connection_data.hh"
#include "instance_info.hh"

namespace ircpp {
namespace detail {

struct instance_data {
    instance_data( 
        irc_data &          irc_,
        connection_data &   conn_ );

    irc_data & irc();
    irc_data const & irc() const;
    
    connection_data & conn();
    connection_data const & conn() const;
    
    std::ostream & log() const;
    
    instance_info & info();
    instance_info const & info() const;
    
protected:
    std::reference_wrapper<irc_data> m_irc;
    std::reference_wrapper<connection_data> m_conn;
    std::shared_ptr<instance_info> m_info;
};

}}

#endif //GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
