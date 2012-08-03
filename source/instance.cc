#include <irc++/irc++.hh>
#include <irc++/client.hh>
#include <irc++/private/detail.hh>


namespace ircmm {

struct instance::impl {
	impl()
	: detail( new ircmm_detail() ) 
	{}

	std::unique_ptr<ircmm_detail> detail;
};

instance::instance() 
: m_internal( new impl() )
{}

std::shared_ptr<client> instance::create_client() {
	return std::make_shared<client>(*m_internal->detail);
}


}

