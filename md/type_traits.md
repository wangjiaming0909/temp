# type_traits
### integral_constant
```c++
template <typename _Tp, _Tp __v>
struct integral_constant{
    typedef _Tp                             value_type;
    typedef integral_constant<_Tp, __v>     type;

    static constexpr _Tp                    value = __v;
    //此函数是此类向_Tp类型的一个隐式转换
    constexpr operator value_type() const {return value;}
    constexpr value_type operator()()const {return value;}
};

//true_type
typedef integral_constant<bool, true> true_type;

//false_type
typedef integral_constant<bool, false> false_type;
```

### is_array
```c++
/// is_array
//如果不匹配一下两个特例话, 就不是array类型
template<typename>
struct is_array : public false_type { };

//数组,定长数组
template<typename _Tp, std::size_t _Size>
struct is_array<_Tp[_Size]> : public true_type { };

//数组,不定长数组
template<typename _Tp>
struct is_array<_Tp[]> : public true_type { };

```

### is_function
好多....

### remove_reference
```c++
//不满足下面两个特例化模板不用remove直接返回_Tp
  /// remove_reference
  template<typename _Tp>
    struct remove_reference
    { typedef _Tp   type; };

  template<typename _Tp>
    struct remove_reference<_Tp&>
    { typedef _Tp   type; };

  template<typename _Tp>
    struct remove_reference<_Tp&&>
    { typedef _Tp   type; };
```

### decay
```c++
// Decay trait for arrays and functions, used for perfect forwarding
// in make_pair, make_tuple, etc.
template<typename _Up, 
    bool _IsArray = is_array<_Up>::value,
    bool _IsFunction = is_function<_Up>::value> 
struct __decay_selector;

template<typename _Up> 
struct __decay_selector<_Up, false, false>
{ typedef typename remove_cv<_Up>::type __type; };

template<typename _Up> 
struct __decay_selector<_Up, true, false>
{ typedef typename remove_extent<_Up>::type* __type; };

template<typename _Up> 
struct __decay_selector<_Up, false, true>
{ typedef typename add_pointer<_Up>::type __type; };

/// decay
template<typename _Tp> 
class decay { 
    typedef typename remove_reference<_Tp>::type __remove_type;
public:
    //如果去掉reference之后是一个数组，就返回一个指针
    //如果去掉reference之后是一个函数类型，就返回一个函数指针
    //标准库这么说：
    /*This behavior is similar to the 
        lvalue-to-rvalue,
        array-to-pointer, and 
        function-to-pointer conversions
applied when an lvalue expression is used as an rvalue, 
but alse strips cv-qualifiers from class types in order to more
closely model by-value argument passing*/
    typedef typename __decay_selector<__remove_type>::__type type;
};
```

