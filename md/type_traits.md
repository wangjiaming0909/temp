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

