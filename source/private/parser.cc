#include "parser.hh"
#include <algorithm>

namespace ircpp {
namespace detail {
namespace parser {

    struct message_parser {
        static bool parse( std::string const & line, message_data & data )
        {
            message_data pdata;
            bool success = message_parser( line.begin(), line.end(), pdata ).success;
            if( success )
            {
                data = pdata;            
            }
            return success;
        }
    private:
        message_parser( std::string::const_iterator begin, std::string::const_iterator end, message_data & data )
        : b( begin )
        , e( end )
        , d( data )
        , success( false )
        {
            parse();
        }
        
        void parse()
        {
            parse_sender();
        }
        
        void parse_token( std::string & token )
        {
            while( b != e && *b == ' ' ) 
            {
                ++b;
            }

            std::string::const_iterator r = std::find( b, e, ' ' );
            token.assign( b, r );
            
            if( r != e ) 
            {
                ++r;
            }
            
            b = r;
        }
        
        void parse_sender()
        {   
            if( b != e ) 
            {
                if( *b == ':' )
                {
                    ++b;
                    parse_token( d.sender );
                }
                parse_command();
            }
        }

        void parse_command()
        {
            parse_token( d.command );
            parse_arguments();
        }
        
        void parse_arguments()
        {   
            success = true;
            while( b != e ) 
            {
                if( *b == ':' )
                {
                    ++b;
                    d.arguments.push_back( std::string(b,e) );
                    b = e;
                }
                else
                {
                    std::string arg;
                    parse_token( arg );            
                    if( !arg.empty() )
                    {
                        d.arguments.push_back( arg );
                    }
                    else
                    {
                        success = false;
                        break;
                    }
                }
            }            
        }
        
    private:
        std::string::const_iterator b;
        std::string::const_iterator e;
        message_data & d;
        bool success;
    };
    
}

bool parse_message( std::string const & line, message_data & data )
{
    if( line.empty() ) {
        return false; // invalid message
    }
    
    return parser::message_parser::parse( line, data );
}    

}}

#ifdef IRCPP_PARSER_TEST
#include <iostream>

void test(char const * msg)
{
    std::cout << "Parsing: '" << msg << "'" << std::endl;
    ircpp::detail::message_data data;
    if( ircpp::detail::parse_message( msg, data ) ) {
        std::cout << "Parsing succeeded" << std::endl;
        std::cout << "Source:  " << data.sender << std::endl;
        std::cout << "Command: " << data.command << std::endl;
        std::cout << "Arguments: " << std::endl;
        for( std::string const & s : data.arguments )
        {
                std::cout << "\t-> " << s << std::endl;
        }
    }
    else {
        std::cout << "FAILURE: " << msg << std::endl;
    }
}

int main(int argc, char const ** argv)
{
    test(":irc.eagle.y.se 251 evilbitch :There are 10 users and 1937 invisible on 5 servers");
    test("PING :foobar");
}


#endif
