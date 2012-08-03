#ifndef GUARD_IRCMM_CLIENT_HH_INCLUDED
#define GUARD_IRCMM_CLIENT_HH_INCLUDED

#include "compiler_fix.hh"

#include <typeinfo>
#include <string>
#include <tuple>
#include <array>
#include <vector>
#include <functional>
#include <stdexcept>
#include <stdexcept>

namespace ircmm {
		
	// Stable API - don't remove any. Deprecated apis have to be marked however not to be removed
	enum message_type {		
		msg_ping 		= 0,
		msg_nick 		= 1,
		msg_join 		= 2,
		msg_channel_users	= 3,
		msg_part		= 4,
		msg_kick		= 5,
		msg_topic		= 6,
		msg_topic_info		= 7,
		msg_mode		= 8,
		msg_005			= 9,
		msg_whois_reply		= 10,
		msg_fallback		= 11,

		// Leave this always as the last entry
		msg_count
	};

	static char const * command_name_by_type[msg_count] = {
		"PING",
		"NICK",
		"JOIN",
		"NAMES",
		"PART",
		"KICK",
		"TOPIC",
		"TOPICINFO",
		"MODE",
		"005",
		"WHOIS",
		"$"
	};	

	struct ircmm_detail;
	struct command {};
	struct message {
		typedef std::pair<char const *, char const *> string_range;
		std::string  full;
		string_range nick;
		string_range ident;
		string_range host;
		string_range target;
		string_range command;
		std::vector<string_range> arguments; 
	};

	struct invalid_command : std::runtime_error {
		invalid_command( std::string cmd ) 
		: std::runtime_error( cmd )
		{}
	};

	template< message_type MessageType >
	struct concrete_message : message {
		enum { value = MessageType };

		static constexpr message_type type() { return MessageType; }
		static constexpr char const * name() { return command_name_by_type[MessageType]; }

		concrete_message( message const & m )
		: message( m ) 
		{
		}
	};

	namespace commands {
		struct ping : concrete_message<msg_ping> {
			ping( message const & m )
			: concrete_message<msg_ping>( m ) 
			{}
		};
	}

	class client;

	template< typename MessageType >
	struct basic_message_handler {
		typedef MessageType param_type;
		static const message_type type = MessageType::value;
		std::function< void (client &, param_type const &) > handler;
	};


	class client {
	public:
		typedef void (*plain_handler_type)( client &, message const &, void * );
		typedef std::function< void(client&, message const &) > handler_type;
	public:
		client(ircmm::ircmm_detail &);
		
		void connect( std::string server, std::string port = "6667" );
		void post( command const & cmd );
		
		void test_trigger_all_handlers();
		
		template< typename Handler >
		void add_handler( Handler handler ) {
			static_assert(
				ircmm::msg_count < Handler::Type && Handler::Type > 0, 
				"client.add_handler<Handler>: invalid handler" 
			);
			m_handlers[Handler::type] = 
				[=]( client & c, message const & m ){ 
					handler.handler( c, static_cast<typename Handler::param_type const &>(m) ); 
				};
		}

		void add_handler( message_type type, handler_type handler );
		void add_handler( message_type type, plain_handler_type handler, void * user_data );
		void clear_handler( message_type type );
		handler_type get_handler( message_type type ) const;
	private:
		// Not default constructible
		client() = delete;
		// Not copyable 
		client(client const &) = delete;
		client & operator=(client) = delete;
		// Not movable
		client(client &&) = delete;
		client & operator=(client &&) = delete;
	private:
		std::array< handler_type, ircmm::msg_count > m_handlers;
		ircmm::ircmm_detail & m_detail;
	};
}

#endif //GUARD_IRCMM_CLIENT_HH_INCLUDED

