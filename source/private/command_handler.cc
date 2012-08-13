//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "command_handler.hh"
#include "commands.hh"
#include <irc++/handler_base.hh>

namespace ircpp {
namespace detail {
    
void internal_command_handler( 
    instance_data instance, 
    message_data const & message )
{
    if( message.command == "PING" ) {
        command::pong( instance, message );
    }
}

void command_dispatcher( 
    instance_data instance, 
    message_data const & message )
{
    instance.handler()->on_command( instance.connection(), message.sender, message.command, message.arguments );
}

void command_handler( 
    instance_data instance, 
    message_data const & message )
{
    internal_command_handler( instance, message );
    command_dispatcher( instance, message );
}

}}
#include "command_handler.hh"
#include "commands.hh"
#include <irc++/handler_base.hh>

namespace ircpp {
namespace detail {
    
void internal_command_handler( 
    instance_data instance, 
    message_data const & message )
{
    if( message.command == "PING" ) {
        command::pong( instance, message );
    }
}

void command_dispatcher( 
    instance_data instance, 
    message_data const & message )
{
    instance.handler()->on_command( instance.connection(), message.sender, message.command, message.arguments );
}

void command_handler( 
    instance_data instance, 
    message_data const & message )
{
    internal_command_handler( instance, message );
    command_dispatcher( instance, message );
}

}}
