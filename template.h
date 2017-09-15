#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

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
        template <class T>
        void operator()(T *p) const {
            os << "deleted.." << std::endl;
            delete p;
        }
    private:
        std::ostream &os;
    };

}
#endif //_TEMPLATE_H_