#ifndef GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED

#include "instance_data.hh"

namespace ircpp {
namespace detail {

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
