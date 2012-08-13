//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "commands.hh"

namespace ircpp {
namespace detail {
namespace command {

void pong( instance_data instance, message_data const & message )
{
    instance.connection().send( std::string(), "PONG", message.arguments );
}


}}}#include "commands.hh"

namespace ircpp {
namespace detail {
namespace command {

void pong( instance_data instance, message_data const & message )
{
    instance.connection().send( std::string(), "PONG", message.arguments );
}


}}}