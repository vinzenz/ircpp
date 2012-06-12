#ifndef GUARD_IRCMM_CLIENT_HH_INCLUDED
#define GUARD_IRCMM_CLIENT_HH_INCLUDED

#include <typeinfo>
#include <tuple>
#include <array>
#include <functional>
#include <stdexcept>

namespace ircmm {
	
	// Stable API - don't remove any. Deprecated apis have to be marked however not to be removed
	enum message_type {		
		msg_ping 			= 0,
		msg_nick 			= 1,
		msg_join 			= 2,
		msg_channel_users	= 3,
		msg_part			= 4,
		msg_kick			= 5,
		msg_topic			= 6,
		msg_topic_info		= 7,
		msg_mode			= 8,
		msg_005				= 9,
		msg_whois_reply		= 10,
		msg_fallback		= 11,

		// Leave this always as the last entry
		msg_count
	};

	struct command {};
	struct message {};

	class client;

	template< typename MessageType >
	struct basic_message_handler {
		typedef MessageType param_type;
		static const message_type type = MessageType::value;
		std::function< void (client &, param_type const &) > handler;
	};


	class client {
	public:
		client(ircmm::instance &);
		
		void connect( std::string server, std::string port = "6667" );
		void post( command const & cmd );
		
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

		void add_handler( message_type type, void (*handler)( client &, message const &, void * ), void * user_data ) {
			if( type >= ircmm::msg_fallback || type < 0 ) {
				throw std::out_of_range("client.add_handler: invalid message_type parameter.");
			}
			m_handlers[type] = [=]( client & c, message const & m ){ handler(c, m, user_data); };
		}
	private:
		std::array< std::function< void( client &, message const & ) >, ircmm::msg_count > m_handlers;
	};
}

#endif //GUARD_IRCMM_CLIENT_HH_INCLUDED

