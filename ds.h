#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//2,返回数组a[0:n-1]的数值个数
namespace ds{
template <class T, size_t N>
constexpr size_t count(const T (&)[N] ){//数组的引用const T(&t)[N]
    return N;
}
//3,给数组begin-end-1赋值value
template <class T, size_t N>
void fill(T(&t)[N], size_t begin, size_t end, const T &value){
    size_t nums = (end - begin);
    if(end > N) throw range_error("out of array range");
    for(size_t i = 0; i < nums; i++){
        t[begin + i] = value;
    }
}
//遍历可以打印的数组
template <class T, size_t N>
void visitarray(const T(&t)[N]){
    for(size_t i = 0; i < N; i++){
        cout << t[i] << " ";
    }
    cout << endl;
}
//4  T只能是数字
template <class T, size_t N>
T inner_product(const T(&t1)[N], const T(&t2)[N]){
    T r = 0;
    for(size_t i = 0; i < N; i++){
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
    if(0 == n)
        return 1;
    else if(1 == n)
        return 2;
    else
        return  fibonacci(n - 1) + fibonacci(n - 2);
}
//20 非递归计算斐波那契数
int fibonacci2(int f0, int f1, int n){
    vector<int> v(n + 1);
    v[0] = f0;
    v[1] = f1;
    for(int i = 2; i < n + 1; i++){
        v[i] = v[i-1] + v[i-2];
    }
    return v[n];
}

//21
//递归  x是奇数 f(x)=f(3x+1), x是偶数，f(x)=x/2
int fx(int x){
    return (0 == x % 2) ? x/2 : fx(3*x+1);
}
// min


}

//为一个二维数组分配内存空间
