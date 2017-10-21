#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <memory>
#include <boost/make_unique.hpp>
#include <vector>

class test{
public:
        test() : b(false) { cout << "test constructor.." << endl; }
        explicit test(int a) : b(a){}
        test(const test &nb) : b(nb.b){}
        // test(const test &&nb) : b(nb.b){}
        void print() { cout << "asd" << b << endl; }
        ~test() { cout << "test deconstructor.." << endl; }

private:
        bool b = true;
};

void main_scoped_array(){
        // boost::scoped_array<test> scoparr(new test[10] ());
        // boost::scoped_array<int> scop_int(new int[10]);
        // boost::scoped_array<test> scop_test = boost::make_unique<test[]>(10);
        // unique_ptr<test> unitest = boost::make_unique<test>(10);
        test t(10);
        //call the rvalue reference of make_unique
        unique_ptr<test> unitestrvalue = boost::make_unique<test>(std::move(t));
        // unique_ptr<test[]> unitest2 = boost::make_unique<test[]>();
        // fill_n(&scop_int[0], 10, 1);
        // fill_n(scop_int, 10, 1);
}

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