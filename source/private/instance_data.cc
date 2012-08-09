#include "instance_data.hh"
#include <irc++/irc++.hh>

namespace ircpp {
namespace detail {
instance_data::instance_data( 
    irc_data &          irc_,
    connection_data &   conn_,
    std::shared_ptr<handler_base_t> handler_ ) 
: m_irc( irc_ )
, m_conn( conn_ )
, m_info( std::make_shared<instance_info>() )
, m_handler( handler_ )
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
#if 0    
std::ostream & instance_data::log() const {
    return const_cast<std::ostream &>(m_irc.get().logstream) 
            << "[" << info().connection.server << "] ";
}
#endif
instance_info & instance_data::info() {
    return *m_info;
} 
    
instance_info const & instance_data::info() const {
    return *m_info;
} 

std::shared_ptr<handler_base_t> & instance_data::handler() {
    return m_handler;
}

std::shared_ptr<handler_base_t> & instance_data::handler() const {
    return const_cast< std::shared_ptr<handler_base_t> & >( m_handler );
}

void instance_data::log_debug( 
    std::string const & who, 
    std::string const & what ) const
{
    handler()->on_log_message( log_severity_t::log_debug, who, what );
}

void instance_data::log_info( 
    std::string const & who, 
    std::string const & what ) const
{
    handler()->on_log_message( log_severity_t::log_info, who, what );
}

void instance_data::log_warn( 
    std::string const & who, 
    std::string const & what ) const
{
    handler()->on_log_message( log_severity_t::log_warn, who, what );
}

void instance_data::log_error( 
    std::string const & who, 
    std::string const & what ) const
{
    handler()->on_log_message( log_severity_t::log_error, who, what );
}

}}
