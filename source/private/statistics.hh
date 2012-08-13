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
