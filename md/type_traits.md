#   1. integral_constant
```c++
template <typename _Tp, _Tp __v>
struct integral_constant{
    static constexpr _Tp            value = __v;
    typedef _Tp                         value_type;
    typedef integral_constant<_Tp, __v> type;
    constexpr operator value_type() const {return value;}
    
};
```