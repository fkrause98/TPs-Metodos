#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <type_traits>
template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> struct Matrix{
   T some_field;
};
