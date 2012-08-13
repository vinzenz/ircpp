//  (C) 2012 Vinzenz Feenstra
//  Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "parser.hh"
#include <algorithm>

namespace ircpp {
namespace detail {
namespace parser {

    /** @brief IRC message parsing implementation
     */
    struct message_parser {
        
        /**
         * @brief uses the class to parse a message into message_data
         * @param line input - message string
         * @param data output - parsed result
         * @return returns false if parsing failed, otherwise it will return true
         */
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
        
        /**
         * @brief parses a token in between spaces
         * @param token token parse result
         */        
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
        
        /**
         * @brief parses the sender out of the message
         */
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

        /**
         * @brief parses the command out of the message
         */
        void parse_command()
        {            
            parse_token( d.command );
            parse_arguments();
        }
        
        /**
         * @brief parses the arguments out of the message
         */
        void parse_arguments()
        {   
            success = true;
            while( b != e ) 
            {
                if( *b == ':' ) // Trailing argument?
                {
                    ++b;
                    d.arguments.push_back( std::string(b,e) );
                    b = e;
                }
                else // Non trailing argument
                {
                    std::string arg;
                    parse_token( arg );            
                    if( !arg.empty() )
                    {
                        d.arguments.push_back( arg );
                    }
                    else // Something is fishy here
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

/**
 * @brief parses an IRC message
 * @param line input - Message to be parsed
 * @param data output - parsing result
 * @return returns true if the message was parsed correctly
 */
bool parse_message( std::string const & line, message_data & data )
{
    if( line.empty() ) {
        return false; // invalid message
    }
    
    return parser::message_parser::parse( line, data );
}    

}}
#include "parser.hh"
#include <algorithm>

namespace ircpp {
namespace detail {
namespace parser {

    /** @brief IRC message parsing implementation
     */
    struct message_parser {
        
        /**
         * @brief uses the class to parse a message into message_data
         * @param line input - message string
         * @param data output - parsed result
         * @return returns false if parsing failed, otherwise it will return true
         */
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
        
        /**
         * @brief parses a token in between spaces
         * @param token token parse result
         */        
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
        
        /**
         * @brief parses the sender out of the message
         */
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

        /**
         * @brief parses the command out of the message
         */
        void parse_command()
        {            
            parse_token( d.command );
            parse_arguments();
        }
        
        /**
         * @brief parses the arguments out of the message
         */
        void parse_arguments()
        {   
            success = true;
            while( b != e ) 
            {
                if( *b == ':' ) // Trailing argument?
                {
                    ++b;
                    d.arguments.push_back( std::string(b,e) );
                    b = e;
                }
                else // Non trailing argument
                {
                    std::string arg;
                    parse_token( arg );            
                    if( !arg.empty() )
                    {
                        d.arguments.push_back( arg );
                    }
                    else // Something is fishy here
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

/**
 * @brief parses an IRC message
 * @param line input - Message to be parsed
 * @param data output - parsing result
 * @return returns true if the message was parsed correctly
 */
bool parse_message( std::string const & line, message_data & data )
{
    if( line.empty() ) {
        return false; // invalid message
    }
    
    return parser::message_parser::parse( line, data );
}    

}}
