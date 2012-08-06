#ifndef GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED

#include "connection_data.hh"

namespace ircpp {
namespace detail {

struct instance_data {
    instance_data( 
        irc_data &          irc_,
        connection_data &   conn_ ) 
    : m_irc( irc_ )
    , m_conn( conn_ )
    {}

    irc_data & irc()
    {
        return m_irc.get();
    }

    irc_data const & irc() const
    {
        return m_irc.get();
    }

    connection_data & conn()
    {
        return m_conn.get();
    }
    
    connection_data const & conn() const
    {
        return m_conn.get();
    }
    
protected:
    std::reference_wrapper<irc_data> m_irc;
    std::reference_wrapper<connection_data> m_conn;
};

void next_read( 
    instance_data   instance );

void send_message( 
    instance_data       instance,
    std::string const & message );


void handle_message(
    instance_data                       instance,
    boost::system::error_code const &   ec,
    size_t                              bytes_read );

void handle_connected( 
    instance_data   instance );

bool next_connect(
    instance_data           instance,
    tcp::resolver::iterator endpoint_iterator );

void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err );

void handle_resolve( 
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator,
    boost::system::error_code const &   err );
}}

#endif //GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
