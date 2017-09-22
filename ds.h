#include <iostream>
#include <cassert>
using namespace std;

//2,返回数组a[0:n-1]的数值个数
namespace ds{
template <class T, size_t N>
constexpr size_t count(const T (&t)[N] ){//数组的引用const T(&t)[N]
    return N;
}
//3,给数组begin-end-1赋值value
template <class T, size_t N>
void fill(T(&t)[N], size_t begin, size_t end, const T &value){
    size_t nums = (end - begin);
    if(end > N) throw range_error("out of array range");
    for(int i = 0; i < nums; i++){
        t[begin + i] = value;
    }
}
//遍历可以打印的数组
template <class T, size_t N>
void visitarray(const T(&t)[N]){
    for(int i = 0; i < N; i++){
        cout << t[i] << " ";
    }
    cout << endl;
}
//4  T只能是数字
template <class T, size_t N>
T inner_product(const T(&t1)[N], const T(&t2)[N]){
    T r = 0;
    for(int i = 0; i < N; i++){
        r += t1[i] * t2[i];
    }
    return r;
}
//19
//非递归计算n!
long long int jiecheng(int t){
    long long int temp = 1;
    for(; t!= 0; t--)
        temp *= t;
    return temp;
}
//20
//递归计算斐波纳挈数
int fibonacci(int n){
    if(n = 0)
        return 1;
    else if(n = 1)
        return 2;
    else
        return  fibonacci(n - 1) + fibonacci(n - 2);

}

}

//为一个二维数组分配内存空间
