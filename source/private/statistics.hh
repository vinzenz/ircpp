//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED

#include <cstdint>

namespace ircpp {
namespace detail {

struct statistics {   
    struct transfer {
        std::uint64_t read;
        std::uint64_t written;
    } bytes_transferred;
    struct message_count {
        std::uint64_t sent;
        std::uint64_t received;
    } messages;
};

}}

#endif //GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED
#ifndef GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED

#include <cstdint>

namespace ircpp {
namespace detail {

struct statistics {   
    struct transfer {
        std::uint64_t read;
        std::uint64_t written;
    } bytes_transferred;
    struct message_count {
        std::uint64_t sent;
        std::uint64_t received;
    } messages;
};

}}

#endif //GUARD_IRCPP_PRIVATE_STATISTICS_HH_INCLUDED
