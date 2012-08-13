#ifndef GUARD_IRCPP_PRIVATE_PARSER_HH_INCLUDED
#define GUARD_IRCPP_PRIVATE_PARSER_HH_INCLUDED

#include <vector>
#include <string>

namespace ircpp {
namespace detail {

struct message_data {
    message_data()
    : sender()
    , command()
    , arguments()
    {}

    std::string sender;
    std::string command;
    std::vector<std::string> arguments;
};

bool parse_message( std::string const & line, message_data & data );

}}

#endif //GUARD_IRCPP_PRIVATE_PARSER_HH_INCLUDED

