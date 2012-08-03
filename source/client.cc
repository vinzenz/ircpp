#include <irc++/client.hh>
#include <irc++/private/detail.hh>

namespace ircmm {

client::client( ircmm::ircmm_detail & d )
: m_detail( d )
{
}

void client::connect( std::string server, std::string port /*= "6667"*/ ) {
	(void)server;
	(void)port;
	
}

void client::post( command const & cmd ) {
	(void)cmd;
}

void client::add_handler( message_type type, handler_type handler ) {
	if( type >= ircmm::msg_fallback || type < 0 ) {
		throw std::out_of_range("client.add_handler: invalid message_type parameter.");
	}
	m_handlers[type] = handler;
}

void client::add_handler( message_type type, plain_handler_type handler, void * user_data ) {
	add_handler( 
		type, 
		[=]( client & c, message const & m ) { 
			handler(c, m, user_data); 
		}
	);
}

void client::test_trigger_all_handlers() {
	for( handler_type & h : m_handlers ) {
		if( h ) {
			h( *this, message() );
		}
	}
}

void client::clear_handler( message_type type ) {
	if( type >= ircmm::msg_fallback || type < 0 ) {
		throw std::out_of_range("client.clear_handler: invalid message_type parameter.");
	}
	m_handlers[type] = handler_type();
}

client::handler_type client::get_handler( message_type type ) const {
	if( type >= ircmm::msg_fallback || type < 0 ) {
		throw std::out_of_range("client.get_handler: invalid message_type parameter.");
	}
	return m_handlers[type];
}

}
