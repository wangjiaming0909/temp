#ifndef _MULTIPLE_INHERITANCE_H_
#define _MULTIPLE_INHERITANCE_H_

#include <string>
#include <ostream>
using namespace std;

namespace _MULTI_INHERITANCE{
class Base1{
public:
    void print(ostream& os, const string &s){os << s << endl;}
private:
    int i;
};

class Base2{
private://即使改成私有的依然导致二义性问题
    // void print(ostream &os, const string &s){os << s << endl;}//形参列表与Base1相同，导致继承类调用时，二义性问题
    void print(ostream &os, int i){os << i << endl;}//形参列表不同，依然存在二义性
    //因为它是先查找名字，再进行类型检查的，因此只要出现名字相同的函数，就存在二义性问题
    //为了规避这种二义性问题，最好的办法是在继承类中定义自己的新版本
};

class Inheritance : public Base1, public Base2{
public:
    using Base1::print;//需要将此using语句放在public中，才能在类外调用
    //与构造函数不同，构造函数的using语句不会改变其访问级别
};


}


#endif //_MULTIPLE_INHERIANCE_H_