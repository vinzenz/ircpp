#include "instance_data.hh"

namespace ircpp {
namespace detail {
instance_data::instance_data( 
    irc_data &          irc_,
    connection_data &   conn_ ) 
: m_irc( irc_ )
, m_conn( conn_ )
, m_info( std::make_shared<instance_info>() )
{}

irc_data & instance_data::irc()
{
    return m_irc.get();
}

irc_data const & instance_data::irc() const
{
    return m_irc.get();
}

connection_data & instance_data::conn()
{
    return m_conn.get();
}
    
connection_data const & instance_data::conn() const
{
    return m_conn.get();
}
    
std::ostream & instance_data::log() const {
    return const_cast<std::ostream &>(m_irc.get().logstream) 
            << "[" << info().connection.server << "] ";
}
   
instance_info & instance_data::info() {
    return *m_info;
} 
    
instance_info const & instance_data::info() const {
    return *m_info;
} 

}}
