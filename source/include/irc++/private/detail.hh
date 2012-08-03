#ifndef GUARD_IRCMM_PRIVATE_DETAIL_HH_INCLUDED
#define GUARD_IRCMM_PRIVATE_DETAIL_HH_INCLUDED

#include <boost/asio.hpp>
#include <thread>

#include <cstdio>

namespace ircmm {

	struct ircmm_detail {
		
		ircmm_detail() 
		: service()
		, work(new boost::asio::io_service::work(service))
		, thread( [&](){ return service.run(); } )
		{}

		~ircmm_detail() {
			work.reset();
			thread.join();
		}

		boost::asio::io_service service;
		std::unique_ptr<boost::asio::io_service::work> work;
		std::thread thread;
	};

}

#endif //GUARD_IRCMM_PRIVATE_DETAIL_HH_INCLUDED

