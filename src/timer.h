#ifndef _AL_TIMER_H_
#define _AL_TIMER_H_
#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

namespace al{
class timer{
public:
    timer(const string& s) : timer_(), s_(s){

    }
    ~timer() {
        cout 
            << std::left << std::setw(48) << s_ 
            << std::left << std::setw(24) << std::fixed << timer_.elapsed() 
            << endl;
    }

private:
    boost::timer timer_;
    string s_;
};
}

#endif // _AL_TIMER_H_