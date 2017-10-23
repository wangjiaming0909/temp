### constructors
```c++
vector();
vector(const allocator_type &__a);
//调用 _M_default_initialize，不带值的版本
vector(size_type, const allocator_type &__a = allocator_type());
//调用 _M_fill_initialize，带值的版本
vector(size_type, value_type &, const allocator_type &__a = allocator_type());

``` 

### protected functions
```c++
void _M_default_initialize(size_type __n);
void _M_fill_initialize(size_type __n, const value_type &__value);
```