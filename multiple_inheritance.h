#ifndef _MULTIPLE_INHERITANCE_H_
#define _MULTIPLE_INHERITANCE_H_

#include <string>
#include <ostream>
using namespace std;

namespace _MULTI_INHERITANCE{
class Base{
public:
private:
    int i;//基类中定义的i
};


class Base1 : virtual public Base{
public:
    void print(ostream& os, const string &s){os << s << endl;}
public:
    // int i;//如果在Base1和Base2中都不进行定义，则Inheritance只含有一个Base的i
    int i;//如果在其中一个子类中定义了，则子类中i比基类中i优先级高，会优先调用

};

class Base2 : virtual public Base{
public:
    // int i;//如果在两个子类中都定义了i, 则将产生二义性
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
namespace _MULTI_INHERITANCE2{
    using namespace std;
    struct Base{
        void bar(int){cout << "bar int" << endl;}
    protected:
        int ival;
    };
    struct Derived1 : virtual public Base{
        void bar(char){cout << "bar char" << endl;}
        void foo(char){cout << "foo char" << endl;}
    protected:
        char ival;
    };

    struct Derived2 : virtual public Base{
        void foo(int){cout << "foo int" << endl;}
    protected:
        int ival;//二义性
        char cval;
    };

    class VMI : public Derived1, public Derived2{
    public:
        void print(){
            // cout << ival << " ";
            // ival = 12;
            cout << Derived1::ival << " ";
            cout << Derived2::ival << " ";
            
            cout << cval << " ";
            // foo(1);//二义性
            Derived1::foo('q');
            Derived1::foo(1);
            Derived2::foo('q');
            Derived2::foo(1);
            // foo('q');//二义性

            Base::bar(1);
            bar(1);//因为子类中的bar函数优先级高，因此隐藏了父类Base中的bar函数，但是也可以直接进行调用
            bar('q');
        }
    };

}

#endif //_MULTIPLE_INHERIANCE_H_