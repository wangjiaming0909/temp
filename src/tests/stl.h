#ifndef _STL_H_
#define _STL_H_

#include <iostream>
#include <vector>
#include <new>
#include <list>
using namespace std;

#ifndef UINT_MAX
    #define UINT_MAX 65535
#endif
namespace JJ
{
template <class T>
inline T *_allocate(ptrdiff_t size, T *)
{
    set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if(tmp == 0){
        cerr << "out of memory" << endl;
        exit(1);
    }
    return tmp;
}

template <class T>
inline void _deallocate(T* buffer){
    ::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value){
    new(p) T1(value);//placement new
}

template <class T>
inline void _destroy(T* ptr){//destroy object, donot deallocate memory
    ptr->~T();
}

template <class T>
class alloctor
{
  public:
    typedef T               value_type;
    typedef T *             pointer;
    // using pointer = T*;
    typedef const T *       const_pointer;
    typedef T &             reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

    template <class U>
    struct rebind
    {
        typedef allocator <U> other;
    };

    pointer allocate(size_type n, const void *hint = 0)
    {
        return _allocate((difference_type)n, (pointer)0);
    }
    void deallocate(pointer p, size_type n){_deallocate(p);}
    void construct(pointer p, const T& value){_construct(p, value);}
    void destroy(pointer p){_destroy(p);}
    pointer address(reference x){return (pointer)&x;}//return address of a reference
    const_pointer const_address(const_reference x){return (const_pointer)&x;}
    size_type max_size() const{
        return size_type(UINT_MAX/sizeof(T));
    }
};

void (*abc(void (*f)()))(){
    cout << "asd" << endl;
    f = nullptr;
    f();
    return 0;
}

}//end of namespace JJ

//type_traits

template <class T>
void print(T &){
    cout << typeid(T).name() << endl;
}

struct nn{
    char c;
    int i;
    int j;
};
void main_list(){
    // list<nn> l(4);
    // list<nn> l(3, {'a', 1, 2});
    // list<nn>::iterator it = l.begin();
    // cout << it->c << endl;
    list<char> l(4, 'q');
    list<char>::iterator it = l.begin();
    cout << *it << endl;
    it = ++it;
    char z = 'z';
    l.insert(it, z);
    // l.remove('z');
    // l.erase(it);
    l.unique();
    // l.clear();
    cout << *it << endl;
}



#endif //_STL_H_