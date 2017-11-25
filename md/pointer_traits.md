```c++
//pointer_traits的原版本
template <typename _Ptr>
struct pointer_traits{
private:
    template <typename _Tp>
    using __element_type = typename _Tp::element_type;
};
```
```c++
//pointer_traits的 _Tp* 的特例化版本
template <typename _Tp>
struct pointer_traits<_Tp*>{
    //指针
    typedef _Tp* pointer;
    //指针所指对象的类型
    typedef _Tp element_type;
    //difference between pointers
    typedef ptrdiff_t difference_type;

    //other type
    template <typename _Up>
    using rebind = _Up*;

    static pointer
    pointer_to(__make_not_void<element_type>& __r)noexcept
    {return std::addressof(__r);}
};
```

```c++
//stl_deque.h
template <typename _Tp, typename _Ref, typename _Ptr>
struct _Deque_iterator{
private:
    // _Ptr 是一个指针，即 _Tp*, 即 pointer_traits 的特例化版本 pointer_traits<_Tp*>
    //因此 rebind 即为 _Up*
    template <typename _Up>
    using __ptr_to = typename pointer_traits<_Ptr>::template rebind<_Up>;// __ptr_to = _Up*

    template <typename _CvTp>//普通迭代器和 const 迭代器
    using __iter = _Deque_iterator<_Tp, _CvTp&, __ptr_to<_CvTp>>;

public:
    typedef __iter<_Tp>             iterator;
    typedef __iter<const _Tp>       const_iterator;
    typedef __ptr_to<_Tp>           _Elt_pointer;//根据上面 __ptr_to, 即为 _Tp*
    typedef __ptr_to<_Elt_pointer>> _Map_pointer;//根据上面 __ptr_to, 即为 _Elt_pointer*, 即 _Tp**
    //so _Elt_pointer 为 _Tp*
    // _Map_pointer 为 _Tp**
}
```