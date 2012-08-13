#include "commands.hh"

namespace ircpp {
namespace detail {
namespace command {

void pong( instance_data instance, message_data const & message )
{
    instance.connection().send( std::string(), "PONG", message.arguments );
}


}}}