#include <boost/scoped_ptr.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <vector>
using namespace boost;


void main_scoped_ptr(){
    std::vector<int, pool_allocator<int>> v;
    v.push_back(123);
    scoped_ptr<int> scptr(new int);
}