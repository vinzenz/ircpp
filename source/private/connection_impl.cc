//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "connection_impl.hh"

namespace ircpp {
namespace detail {

/**
 * @brief sends a 'line/message' to the server
 * @param instance shared instance data
 * @param line the line/message to be sent
 */
void send_line(
    instance_data instance,
    std::string line )
{
    instance.log_info( "send_line", "MESSAGE SENT: " + line );
    line += "\r\n";
    boost::asio::async_write(
        instance.conn().socket,
        boost::asio::buffer(line),
        [instance](
            boost::system::error_code const & ec,
            std::size_t written )
        {
            if( !ec ) {
                instance_data data = instance_data(instance);
                data.info().stats.bytes_transferred.written += written;
                data.info().stats.messages.sent += 1;
            }
            else {
                instance.log_error( "send_line completion handler", "Sending line failed: " + ec.message() );
            }
        }
    );
}

connection_impl::connection_impl( instance_data instance )
: ircpp::connection()
, instance_( instance ) 
{}

connection_impl::~connection_impl()
{}
    
void connection_impl::send_raw(
    std::string const & raw_message )
{
    send_line( instance_, raw_message );
}

void connection_impl::send(
    std::string const & target,
    std::string const & command,
    std::vector<std::string> const & args )
{
    std::string line;
    if( !target.empty() ) {
        line += ':' + target + ' ';
    }
    
    line += command + ' ';
    
    if( !args.empty() )
    {
        for( size_t i = 0; i < args.size() - 1; ++i ) {
            line += ' ' + args[i];
        }
        line += " :" + args.back();
    }
    
    send_raw( line );
}


}}#include "connection_impl.hh"

namespace ircpp {
namespace detail {

/**
 * @brief sends a 'line/message' to the server
 * @param instance shared instance data
 * @param line the line/message to be sent
 */
void send_line(
    instance_data instance,
    std::string line )
{
    instance.log_info( "send_line", "MESSAGE SENT: " + line );
    line += "\r\n";
    boost::asio::async_write(
        instance.conn().socket,
        boost::asio::buffer(line),
        [instance](
            boost::system::error_code const & ec,
            std::size_t written )
        {
            if( !ec ) {
                instance_data data = instance_data(instance);
                data.info().stats.bytes_transferred.written += written;
                data.info().stats.messages.sent += 1;
            }
            else {
                instance.log_error( "send_line completion handler", "Sending line failed: " + ec.message() );
            }
        }
    );
}

connection_impl::connection_impl( instance_data instance )
: ircpp::connection()
, instance_( instance ) 
{}

connection_impl::~connection_impl()
{}
    
void connection_impl::send_raw(
    std::string const & raw_message )
{
    send_line( instance_, raw_message );
}

void connection_impl::send(
    std::string const & target,
    std::string const & command,
    std::vector<std::string> const & args )
{
    std::string line;
    if( !target.empty() ) {
        line += ':' + target + ' ';
    }
    
    line += command + ' ';
    
    if( !args.empty() )
    {
        for( size_t i = 0; i < args.size() - 1; ++i ) {
            line += ' ' + args[i];
        }
        line += " :" + args.back();
    }
    
    send_raw( line );
}


}}