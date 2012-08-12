#include <boost/asio.hpp>

class coroutine
{
public:
  coroutine() : value_(0) {}
private:
  friend class coroutine_ref;
  int value_;
};

class coroutine_ref
{
public:
  coroutine_ref(coroutine& c) : value_(c.value_) {}
  coroutine_ref(coroutine* c) : value_(c->value_) {}
  operator int() const { return value_; }
  int operator=(int v) { return value_ = v; }
private:
  int& value_;
};

#define reenter(c) \
  switch (coroutine_ref _coro_value = c)

#define entry \
  extern void you_forgot_to_add_the_entry_label(); \
  bail_out_of_coroutine: break; \
  case 0

#define yield \
  if ((_coro_value = __LINE__) == 0) \
  { \
    case __LINE__: ; \
    (void)&you_forgot_to_add_the_entry_label; \
  } \
  else \
    for (bool _coro_bool = false;; \
         _coro_bool = !_coro_bool) \
      if (_coro_bool) \
        goto bail_out_of_coroutine; \
      else

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::buffer;
#include <string>
#include <iostream>

struct irc : coroutine
{
    struct wrapped_impl {
        wrapped_impl( irc * instance ) 
        : instance_( instance )
        {
        }

        wrapped_impl() 
        : instance_( 0 )
        {
        }

        void operator()( error_code const & ec = error_code(), size_t count = 0 ) 
        {
                (*instance_)(ec, count);
        }
    private:
        irc * instance_;
    };

    irc(io_service & service, tcp::endpoint ep)
    : coroutine()
    , io_( service )
    , socket_( io_ )
    , endpoint_( ep )
    , readbuffer_()
    , send_buffer_()
    , wrapped_()
    {
        wrapped_ = wrapped_impl( this );
        socket_.async_connect( ep, wrapped_ );
    }


    void operator()( 
        error_code const & ec = error_code(),
        size_t count = 0 )
    {
        reenter (this)
        {
        entry:            
            std::cout << "Entering coroutine" << std::endl;
            send_buffer_ = "NICK evilbitch\r\nUSER evilbitch 0 * :evilbitch\r\n";
            yield boost::asio::async_write( socket_, buffer(send_buffer_), wrapped_ );

            while( !ec )
            {
                yield boost::asio::async_read_until( socket_, readbuffer_, "\n", wrapped_ );

                if( ec ) break;                
                send_buffer_ = "";
                {
                    std::istream is(&readbuffer_);
                    std::string line;
                    if( std::getline( is, line ) ) {
                        while( !line.empty() && line[line.size() - 1] == '\r' ) line.erase( line.size() - 1 );
                        std::cout << "Received: " << line << std::endl;
                        if( line.substr(4) == "PING" ) {
                            line[2] = 'O';
                            send_buffer_ = line;
                        }
                    }
                }
                yield boost::asio::async_write( socket_, buffer( send_buffer_ ), wrapped_ );
            }
        }
    }

private:
    io_service & io_;
    tcp::socket socket_;
    tcp::endpoint endpoint_;
    boost::asio::streambuf readbuffer_;
    std::string send_buffer_;
    wrapped_impl wrapped_;
};

int main()
{
    io_service service;
    tcp::resolver resolver( service );
    tcp::resolver::query query( "irc.euirc.net", "6667" );
    tcp::resolver::iterator it = resolver.resolve( query );
    irc instance( service, *it ); 
    service.run();
}

