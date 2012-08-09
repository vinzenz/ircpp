#include <irc++/irc++.hh>

int main(){

ircpp::irc instance;

std::shared_ptr<ircpp::handler_t> h = std::make_shared<ircpp::handler_t>();

instance.connect("irc.freenode.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", h);
instance.connect("irc.euirc.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", h);
instance.connect("irc.du.se", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", h);
instance.connect("irc.gnome.org", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", h);

instance.run();

}
