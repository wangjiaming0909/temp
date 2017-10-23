<!-- TOC-->
## GNU STL vector 中的所有构造函数
### 1. `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::vector()`
```c++
vector() noexcept(is_nothrow_default_constructible<_Alloc>::value) : _Base() { }
```
### 2. `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::vector(const allocator_type & __a)`
```c++
explicit vector(const allocator_type & __a) _GLIBCXX_NOEXCEPT : _Base(__a) {} 
```
### 3. `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::vector(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type())`
```c++
vector(size_type __n, 
      const value_type& __value, 
      const allocator_type& __a = allocator_type()) : _Base(__n, __a)
      { _M_fill_initialize(__n, __value); }
```

#### `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::_M_fill_initialize(size_type __n, const value_type &__value)`
```c++
void _M_fill_initialize(size_type __n, const value_type& __value){
    this->_M_impl._M_finish =
        std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, _M_get_Tp_allocator());
}
```
### 4. `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::vector(size_type __n, const allocator_type &__a = allocator_type())`
```c++
vector(size_type __n, const allocator_type &__a = allocator_type()) : _Base(__n, __a)
    {_M_default_initialize(__n);}
```
#### `vector<typename _Tp, typename _Alloc = std::allocator<_Tp>>::_M_default_initialize(size_type __n)`
```c++
void _M_default_initialize(size_type __n){
    this->_M_impl._M_finish = 
        std::__uninitialized_default_n_a(this->_M_impl._M_start, __n, _M_get_Tp_allocator());
}
```
```c++
//带 n 个元素， 带allocator的 uninitialized_default版本
//__unitialized_default_n_a还有一个模板版本，其最后一个模板参数是一个typename _Allocator
//因此次函数的意图是通过模板匹配allocator类型，区分其是否为std::allocator
template<typename _ForwardIterator, typename _Size, typename _Tp> 
inline _ForwardIterator
__uninitialized_default_n_a(_ForwardIterator __first, _Size __n, allocator<_Tp>&)
    { return std::__uninitialized_default_n(__first, __n); }//转化为只带 n 不带a的版本
```
```c++
//__uninitialized_default_n 只有这一个版本
//一般vector是一个random access iterator
  template<typename _ForwardIterator, typename _Size>
inline _ForwardIterator __uninitialized_default_n(_ForwardIterator __first, _Size __n){
	typedef typename iterator_traits<_ForwardIterator>::value_type_ ValueType;
	// trivial types can have deleted assignment
	const bool __assignable = is_copy_assignable<_ValueType>::value;
	return __uninitialized_default_n_1<__is_trivial(_ValueType) && __assignable>::__uninit_default_n(__first, __n);
}
```
```c++
//带 n 个元素， 带allocator的 uninitialized_default版本
//此为自定义allocator所调用的版本
template<typename _ForwardIterator, typename _Size, typename _Allocator>
_ForwardIterator __uninitialized_default_n_a(_ForwardIterator __first, _Size __n, _Allocator& __alloc){
    _ForwardIterator __cur = __first;
    __try{
        typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
        for (; __n > 0; --__n, ++__cur)
            __traits::construct(__alloc, std::__addressof(*__cur));
        return __cur;
    }
    __catch(...){
        std::_Destroy(__first, __cur, __alloc);
        __throw_exception_again;
    }
}
```

## 基类 _Vector_base
### 1. `_Vector_base()`
```c++
_Vector_bse() : _M_impl() { }
```
```c++
_Vector_base(const allocator_type& __a) _GLIBCXX_NOEXCEPT : _M_impl(__a) { }
```


## _Vector_base的内部类 `_Vector_impl : public _Tp_alloc_type`
```c++
_Vector_impl() : _Tp_alloc_type(), _M_start(), _M_finish(), _M_end_of_storage()	{ }
```
```c++
_Vector_impl(_Tp_alloc_type const& __a) _GLIBCXX_NOEXCEPT : 
_Tp_alloc_type(__a), _M_start(), _M_finish(), _M_end_of_storage(){ }
```