#include <boost/scoped_ptr.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <memory>
#include <vector>

class test{
public:
        test() : b(false) { cout << "test constructor.." << endl; }
        void print() { cout << "asd" << b << endl; }
        ~test() { cout << "test deconstructor.." << endl; }

private:
        bool b = true;
};

void main_scoped_ptr()
{
        // std::vector<int, boost::pool_allocator<int>> v;
        // v.push_back(123);
        boost::scoped_ptr<test> scptr(new test);
        scptr.reset();
        // vector<boost::scoped_ptr<test>> v;
        // v.push_back(scptr);//error, cause scoped_ptr constructor is private
        vector<unique_ptr<test>> v2;
        std::unique_ptr<test> uniptr(new test);
        // v2.push_back(static_cast<unique_ptr<test> &&>(uniptr)); //unique_ptr's lvalue copy constructor is deleted
        v2.push_back(std::move(uniptr)); //unique_ptr's rvalue copy constructor is ok
        // uniptr.reset();
        // uniptr->print();
        uniptr->~test();
}