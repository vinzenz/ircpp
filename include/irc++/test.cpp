#include <irc++/irc++.hh>

int main(){

ircpp::irc instance;

instance.connect("irc.freenode.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch");
instance.connect("irc.euirc.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch");
instance.connect("irc.du.se", "6667", "evilbitch", "evilbitch", "foo", "evilbitch");
instance.connect("irc.gnome.org", "6667", "evilbitch", "evilbitch", "foo", "evilbitch");

instance.run();

}
