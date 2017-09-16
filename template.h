#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
//定义一个非类型模版参数
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]){
    return N - M;
}

//模版，第16章
namespace JJ{
    //习题16.4  模拟find
    template <typename It, typename Value_type>
    It find(It _it1, It _it2, const Value_type &v){
        It temp = _it2;
        for(auto it = _it1; it != _it2; it++){
            if(v == *it)
                temp = it;
        }
        return temp;
    }

    //习题16.6  定义数组的begin和end
    //返回非const版本，这样可以用户可以使用这个迭代器修改这个数组
    template <unsigned N, typename T>
    T* begin(const T(&a)[N]){
        return const_cast<T*>(a + 0);
    }
    // auto begin(const T(&a)[N] )->decltype(a){
    //     return a;
    // }

    template <unsigned N, typename T>
    T* end(const T(&a)[N]){
        return const_cast<T*>(a + N);
    }
    // auto end(const T(&a)[N])->decltype(a){
    //     return 
    // }

    //16.7 编写一个constexpr模版，返回数组大小
    template <unsigned N, typename T>
    constexpr unsigned array_size(const T(&)[N]){
        return N;
    }

    template <typename T>
    void visit_containers(const T &l){
        auto it = l.begin();
        for(; it != l.end(); it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void visit_containers2(const T &l){
        auto it = begin(l);
        for(; it != end(l); it++)
           std::cout << *it << " ";   
        std::cout << std::endl;
    }

    template <class T>
    class Blob{
    public:
        using value_type = T;
        //这里需要加上typename，可能是因为vector里有一个模版参数
        using size_type = typename std::vector<T>::size_type;
    public:
        Blob();
        Blob(std::initializer_list<T> il);
        size_type size() const {return data->size();}
        bool empty() const {return data->empty();}
        void push_back(const T &t){data->push_back(t);}
        void push_back(T &&t){data->push_back(std::move(t));}
        void pop_back();
        T& back();
        T& operator[](size_type i);
    private:
        void check(size_type i, const std::string &msg) const;
    private:
        std::shared_ptr<std::vector<T>> data;
    };

    class DebugDelete{
    public:
        DebugDelete(std::ostream &o = std::cerr) : os(o){}
        template <class T>
        void operator()(T *p) const {
            os << "deleted.." << std::endl;
            delete p;
        }
    private:
        std::ostream &os;
    };

    // class NoDefault{
    // public:
    //     // NoDefault() = delete;
    //     NoDefault(int m) : a(m){}
    // private:
    //     int a;
    // };

    // template class std::vector<DebugDelete>;

    template <typename T>
    class my_shared_ptr{
    public:

    private:
        
    };

    template <class T> int compare(T &t1, T &t2){
        std::cout << t1 << " " << t2 << std::endl;
        return t1 > t2;
    }

    template <class T>
    T calc(T lhs, T rhs){
        std::cout << lhs << " " << rhs << std::endl;
    }
    template <class T>
    const T& my_max(const T &t1, const T &t2){
        return std::max(t1, t2);
    }

    template <typename It>
    auto return_r_ref(It beg, It end) ->decltype(*beg + 0){//返就是一个右值引用，不是引用类型
        return *beg;
    }

    //检查左右值引用模版的调用问题
    template <typename T>
    void ref(const T &l){
        std::cout << "l" << std::endl;
    }
    // template <typename T>
    // void ref(T &&r){
    //     std::cout << "r" << std::endl;
    // }

    //16.3重载与模版
    template <typename T> 
    std::string debug_rep(const T &t){
        std::ostringstream ret;
        ret << t;
        return ret.str();
    }       

    template <typename T>
    std::string debug_rep(T *p){
        std::ostringstream ret;
        ret << "pointer: " << p;
        if(p) 
            ret << " " <<debug_rep(*p);
        else
            ret << " null pointer";
        return ret.str();
    }

    std::string debug_rep(const std::string &s){
        return '"' + s + '"';
    }
    std::string debug_rep(char *p){
        return debug_rep(std::string(p));
    }
    std::string debug_rep(const char *p){
        return debug_rep(std::string(p));
    }

    //习题16.49
    template <typename T>
    void f(T t){
        std::cout << "f 1" << " ";
        std::cout << t << std::endl;
    }
    template <typename T>
    void f(const T *t){
        std::cout << "f 2" << std::endl;
    }

    template <class T>
    void g(T t){
        std::cout << "g 1" << " ";
        std::cout << t << std::endl;
    }
    template <class T>
    void g(const T *t){
        std::cout << "g 2" << std::endl;
    }
    //可变参数模版
    template <typename ...Args>
    void g(Args ... args){
        using std::cout;
        using std::endl;
        cout << sizeof...(Args) << endl;
        cout << sizeof...(args) << endl;
    }

    template <class T>
    std::ostream &print(std::ostream &os, const T&t){
        return os << t;
    }
    using std::ostream;
    template <typename T, typename... Args>
    ostream &print(ostream &os, const T&t, const Args&... rest){
        os << t << ", ";
        return print(os, rest...);//少了const T&t，因此每次调用包内少一个参数，最终调用非模版的函数
    }

    template <class T>
    struct template_C{
        T i;
    };
    template <class T>
    struct template_C<T *>{
        T i;
    };
    template <class T>
    struct template_C<T&>{
        T i;
    };

};

#endif //_TEMPLATE_H_