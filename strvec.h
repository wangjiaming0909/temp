#ifndef STRVEC_H
#define STRVEC_H
#include <memory>
#include <initializer_list>
#include <iostream>
#include <algorithm>

class StrVec{
    friend std::ostream& operator<<(std::ostream &os, StrVec& str);
    friend std::istream& operator>>(std::istream &is, StrVec& str);
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr){}
    StrVec(std::initializer_list<std::string>);
    StrVec(StrVec &&s) noexcept;
    StrVec& operator =(StrVec &&s) noexcept;
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    StrVec &operator =(std::initializer_list<std::string>);
    StrVec &operator+=(const StrVec&);
    StrVec &operator+=(const std::string &);
    std::string &operator[](std::size_t t){
        return elements[t];
    }
    //对常量对象调用，返回常量std::string，不能对此string赋值
    const std::string &operator[](std::size_t i) const{
        return elements[i];
    }
    ~StrVec(){free();}
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string* begin() const {return elements;}
    std::string* end() const {return first_free;}

    void push_back(const std::string&);
    void push_back(std::string &&);
    bool reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const std::string &s);

private:
    void chk_n_alloc(){
        if(size() == capacity())
            reallocate();
    }
    //当拷贝对象的时候用来分配内存
    std::pair<std::string*, std::string*>
    alloc_n_copy(const std::string* _begin,
                 const std::string* _end);
    std::pair<std::string*, std::string*>
    alloc_n_move(const std::string *_begin,
                 const std::string *_end, size_t n);
    void free();
    void reallocate();

private:
    static std::allocator<std::string> alloc;
    std::string *elements;//指向首元素
    std::string *first_free;//指向第一个空闲元素
    std::string *cap;//指向数组尾后位置的指针
};

#endif // STRVEC_H

