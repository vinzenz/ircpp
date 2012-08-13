#ifndef GUARD_IRCPP_PRIVATE_COMMAND_HANDLER_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_COMMAND_HANDLER_HH_INCLUDED

#include "parser.hh"
#include "instance_data.hh"

namespace ircpp {
namespace detail {

void command_handler( instance_data instance, message_data const & message );

}}

#endif //GUARD_IRCPP_PRIVATE_COMMAND_HANDLER_HH_INCLUDED

