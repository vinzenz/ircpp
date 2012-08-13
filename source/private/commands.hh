//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_COMMANDS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_COMMANDS_HH_INCLUDED

#include "instance_data.hh"
#include "parser.hh"

namespace ircpp {
namespace detail {
namespace command {

void pong( instance_data instance, message_data const & message );
    
}}}

#endif //GUARD_IRCPP_PRIVATE_COMMANDS_HH_INCLUDED
