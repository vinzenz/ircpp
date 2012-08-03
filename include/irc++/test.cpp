#include "irc++.hh"
#include "client.hh"
#include <iostream>
#include <functional>

void foo( ircmm::client &, ircmm::message const &, void * param ) {
	std::cout << "foo called with: " << (char const *)param << std::endl;
}

void typed_foo( ircmm::client &, ircmm::message const &, char const * param ) {
	std::cout << "foo called with: " << param << std::endl;
}
int main() {
	ircmm::instance instance;
	std::shared_ptr<ircmm::client> client = instance.create_client();
	using std::placeholders::_1;
	using std::placeholders::_2;
	client->add_handler( ircmm::msg_ping, foo, (void*)"wow" );
	client->add_handler( ircmm::msg_nick, std::bind( typed_foo, _1, _2, "\\o/" )  );
	client->test_trigger_all_handlers();

	client->connect("irc.freenode.net");
}

