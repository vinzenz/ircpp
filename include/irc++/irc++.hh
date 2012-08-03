#ifndef GUARD_IRCMM_IRCMM_HH_INCLUDED
#define GUARD_IRCMM_IRCMM_HH_INCLUDED

#include <memory>

namespace ircmm {

	struct ircmm_detail;
	class client;
	class instance {
	public:
		instance();

		std::shared_ptr<client> create_client();

	private:
		struct impl;
		std::shared_ptr<instance::impl> m_internal;
	};

}

#endif // GUARD_IRCMM_IRCMM_HH_INCLUDED

