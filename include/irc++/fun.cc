#include <functional>
 
struct foo{};
struct bar{};
 
using std::placeholders::_1;
using std::placeholders::_2;
 
void fun( foo &, bar const &, void * ) {}
 
int main() {
        std::function< void( foo &, bar const &, void * ) > f = std::bind( fun, _1, _2, (void*)0 );
 
}
