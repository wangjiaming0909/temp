#include "strvec.h"

std::allocator<std::string> StrVec::alloc;



StrVec::StrVec(std::initializer_list<std::string> il)
{
    auto data = alloc.allocate(il.size());
    auto p = std::uninitialized_copy(il.begin(), il.end(), data);
    elements = data;
    first_free = p;
    cap = elements + il.size();
}

StrVec::StrVec(StrVec &&s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap){
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec &&s) noexcept{
    if(this != &s){//避免自我赋值
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }
    return *this;
}

StrVec::StrVec(const StrVec &s)
{
    auto p = alloc_n_copy(s.elements, s.first_free);
    elements = p.first;
    first_free = cap = p.second;
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
    free();
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    elements = data.first;
    cap = first_free = data.second;
    return *this;
}

StrVec& StrVec::operator =(std::initializer_list<std::string> il)
{
    *this = StrVec(il);
    return *this;
}

StrVec& StrVec::operator+=(const StrVec &str)
{
    for(auto &it : str)
        this->push_back(it);
    return *this;
}

StrVec &StrVec::operator+=(const std::string &s)
{
    this->push_back(s);
    return *this;
}


void StrVec::push_back(const std::string &s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}


std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *_begin, const std::string *_end)
{
    auto data = alloc.allocate(_end - _begin);
    //uninitialized_copy 返回拷贝完最后一个元素的下一个元素
    return make_pair(data, std::uninitialized_copy(_begin, _end, data));
}

void StrVec::free(){
    if(elements){
        std::for_each(elements, first_free, [this](std::string& rhs){alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap - elements);
    }
}

//void StrVec::free()
//{
//    if(elements){
//        for(auto p = first_free; p != elements;)
//            alloc.destroy(--p);//destroy会调用string的析构函数
//        alloc.deallocate(elements, cap - elements);//
//    }
//}

void StrVec::reallocate()
{
    auto newcapacity = size() ? size()*2 : 1;
    auto data = alloc.allocate(newcapacity);
    auto dest = data;
    auto elem = elements;
    for(size_t i = 0; i != size(); i++)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = data;
    first_free = dest;
    cap = elements + newcapacity;
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_move(const std::string *_begin, const std::string *_end, size_t n)
{
    auto data = alloc.allocate(n);
    auto dest = data;
    auto elem = _begin;
    for(int i = 0; i != _end - _begin; i++)
        alloc.construct(dest++, std::move(*elem++));
    free();
    return make_pair(data, dest);
}

bool StrVec::reserve(size_t n)
{
    if(capacity() < n){
        auto p = alloc_n_move(elements, first_free, n);
        elements = p.first;
        first_free = p.second;
        cap = elements + n;
        return false;
    }
    return true;
}

void StrVec::resize(size_t n)
{
    resize(n, std::string());
}

void StrVec::resize(size_t n, const std::string &s)
{
    auto new_n = n - size();
    if(!reserve(n))
        for(size_t i = 0; i < new_n; i++)
            alloc.construct(first_free++, s);
    else
        for(;cap != elements + n;)
            alloc.destroy(--cap);
}


std::ostream& operator<<(std::ostream &os, StrVec &str)
{
    for(size_t i = 0; i != str.size(); i++){
        os << *(str.elements + i) << " ";
    }
    return os;
}

std::istream& operator>>(std::istream &is, StrVec &str)
{
    std::string s;
    while(is >> s){
        str.push_back(s);
        s.clear();
    }
    return is;
}

bool operator==(const StrVec &lhs, const StrVec &rhs)
{
    return (*lhs.elements == *rhs.elements);
}
