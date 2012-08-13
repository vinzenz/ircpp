//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED

#include "connection_data.hh"
#include "instance_info.hh"
#include <irc++/connection.hh>

namespace ircpp {

struct handler_base_t;

namespace detail {    
    
struct instance_data {
    instance_data( 
        irc_data &          irc_,
        connection_data &   conn_,
        std::shared_ptr<handler_base_t> handler_ );

    irc_data & irc();
    irc_data const & irc() const;
    
    connection_data & conn();
    connection_data const & conn() const;
    
    ircpp::connection & connection() const;
#if 0    
    std::ostream & log() const;
#endif    
    instance_info & info();
    instance_info const & info() const;
    
    std::shared_ptr<handler_base_t> & handler();
    std::shared_ptr<handler_base_t> & handler() const;
    
    void log_debug( std::string const & who, std::string const & what ) const;
    void log_info( std::string const & who, std::string const & what ) const;
    void log_warn( std::string const & who, std::string const & what ) const;
    void log_error( std::string const & who, std::string const & what ) const;
protected:
    std::reference_wrapper<irc_data> m_irc;
    std::reference_wrapper<connection_data> m_conn;
    std::shared_ptr<instance_info> m_info;
    std::shared_ptr<handler_base_t> m_handler;
    std::shared_ptr<ircpp::connection> m_send_conn;
};

}}

#endif //GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
#ifndef GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED

#include "connection_data.hh"
#include "instance_info.hh"
#include <irc++/connection.hh>

namespace ircpp {

struct handler_base_t;

namespace detail {    
    
struct instance_data {
    instance_data( 
        irc_data &          irc_,
        connection_data &   conn_,
        std::shared_ptr<handler_base_t> handler_ );

    irc_data & irc();
    irc_data const & irc() const;
    
    connection_data & conn();
    connection_data const & conn() const;
    
    ircpp::connection & connection() const;
#if 0    
    std::ostream & log() const;
#endif    
    instance_info & info();
    instance_info const & info() const;
    
    std::shared_ptr<handler_base_t> & handler();
    std::shared_ptr<handler_base_t> & handler() const;
    
    void log_debug( std::string const & who, std::string const & what ) const;
    void log_info( std::string const & who, std::string const & what ) const;
    void log_warn( std::string const & who, std::string const & what ) const;
    void log_error( std::string const & who, std::string const & what ) const;
protected:
    std::reference_wrapper<irc_data> m_irc;
    std::reference_wrapper<connection_data> m_conn;
    std::shared_ptr<instance_info> m_info;
    std::shared_ptr<handler_base_t> m_handler;
    std::shared_ptr<ircpp::connection> m_send_conn;
};

}}

#endif //GUARD_IRCPP_PRIVATE_INSTANCE_DATA_HH_INCLUDED
