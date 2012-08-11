#include <irc++/irc++.hh>


class my_handler : public ircpp::handler_t {
    std::string network_;
public:
    my_handler(std::string const & network)
    : ircpp::handler_t()
    , network_(network)
    {}

    virtual void on_log_message(
        ircpp::log_severity_t severity,
        std::string const & source,
        std::string const & message )
    {
        std::cout << "[" << network_ << "] <:> ";
        ircpp::handler_t::on_log_message( severity, source, message );
    }
};

int main(){

ircpp::irc instance;

instance.connect("irc.freenode.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", std::make_shared<my_handler>("Freenode") );
instance.connect("irc.euirc.net", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", std::make_shared<my_handler>("euIRC"));
//instance.connect("irc.du.se", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", std::make_shared<my_handler>("du.se"));
instance.connect("irc.gnome.org", "6667", "evilbitch", "evilbitch", "foo", "evilbitch", std::make_shared<my_handler>("GimpNET"));

instance.run();

}
