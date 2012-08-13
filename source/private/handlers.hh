//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED

#include "instance_data.hh"

namespace ircpp {
namespace detail {

/**
 * @brief schedules an asynchronous connect to the resolved host, if applicable
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @return returns true if a connect attempt has been scheduled. It returns false if no endpoints have been resolved or none has been resolved at all 
 */
bool next_connect(
    instance_data           instance,
    tcp::resolver::iterator endpoint_iterator );

/**
 * @brief handles the established or failed connect event, in case of failure it tries to attempt to connect to the next resolved endpoint
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param endpoint last tried endpoint
 * @param err result of connect attempt
 */
void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err );

/**
 * @brief handle_resolve handles the result of resolving the server host
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param err result of resolving host
 */
void handle_resolve( 
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator,
    boost::system::error_code const &   err );
}}

#endif //GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
#ifndef GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED

#include "instance_data.hh"

namespace ircpp {
namespace detail {

/**
 * @brief schedules an asynchronous connect to the resolved host, if applicable
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @return returns true if a connect attempt has been scheduled. It returns false if no endpoints have been resolved or none has been resolved at all 
 */
bool next_connect(
    instance_data           instance,
    tcp::resolver::iterator endpoint_iterator );

/**
 * @brief handles the established or failed connect event, in case of failure it tries to attempt to connect to the next resolved endpoint
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param endpoint last tried endpoint
 * @param err result of connect attempt
 */
void handle_connect( 
    instance_data                       instance,
    tcp::resolver::iterator             endpoint_iterator,
    tcp::endpoint                       endpoint,
    boost::system::error_code const &   err );

/**
 * @brief handle_resolve handles the result of resolving the server host
 * @param instance shared instance data
 * @param endpoint_iterator endpoint iterator
 * @param err result of resolving host
 */
void handle_resolve( 
    instance_data                       instance, 
    tcp::resolver::iterator             endpoint_iterator,
    boost::system::error_code const &   err );
}}

#endif //GUARD_IRCPP_PRIVATE_HANDLERS_HH_INCLUDED
