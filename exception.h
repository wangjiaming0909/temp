#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
#include <string>
#include <iostream>
using namespace std;
namespace EXCEPTION_H_
{
template <class T>
class A
{
  public:
    A(string _s);

  private:
    string s;
};

template <class T>
A<T>::A(string _s) try : s(_s)
{
}
catch (const std::bad_alloc &e)
{
    cout << "bad_alloc" << endl;
}

void print(const string &s) noexcept{
    cout << s << endl;
}
}
#endif //EXCEPTION_H_