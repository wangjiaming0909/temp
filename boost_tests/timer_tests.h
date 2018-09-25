#include <iostream>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <unistd.h>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace boost_test{

void hello(int i){
    std::cout << i << std::endl;
}

using namespace boost;
class test_timer{
public:
    static void test(){
        timer t;
        std::cout << t.elapsed_max() << std::endl;
        std::cout << t.elapsed_min() << std::endl;
    }
    static void test2(){
        progress_timer t(std::cout);
        
        for(long i = 0; i < 10000; i++)
        {
            std::cout << i << std::endl;
        }
    }
    static void test3(){
        progress_display pd(100, cout, "%%%", "+++", "???");
        for(int i = 0; i < 10000; i++){
            if(i % 100 == 0){
                sleep(1);
                ++pd;
            }
        }
    }
    static void test4(){
        using namespace boost::gregorian;
        date d(2018, 1, 1);
        std::cout << d << std::endl;
    }
};


}