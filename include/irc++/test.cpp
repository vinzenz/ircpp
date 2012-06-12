#include "irc++.hh"
#include "client.hh"

int main() {
	ircmm::instance instance;
	ircmm::client client(instance);
}

