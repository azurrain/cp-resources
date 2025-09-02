#ifndef CPLIB_BIT_HPP
#define CPLIB_BIT_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<integral T>
constexpr T floor2(T x) {
    return bit_floor(make_unsigned_t<T>(x));
}
template<integral T>
constexpr T ceil2(T x) {
    return bit_ceil(make_unsigned_t<T>(x));
}
template<integral T>
constexpr int ilog2(T x) {
    return bit_width(make_unsigned_t<T>(x)) - 1;
}
template<integral T>
constexpr int popcnt(T x) {
    return popcount(make_unsigned_t<T>(x));
}

}  // namespace cplib

#endif  // CPLIB_BIT_HPP
