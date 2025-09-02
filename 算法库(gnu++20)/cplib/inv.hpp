#ifndef CPLIB_INV_HPP
#define CPLIB_INV_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<signed_integral T>
constexpr pair<T, T> inv_gcd(T x, T m) {
    T u = 1;
    T v = 0;
    T y = m;
    while (x != 0) {
        T t = y / x;
        y -= t * x;
        v -= t * u;
        swap(x, y);
        swap(u, v);
    }
    if (y < 0) {
        v = -v;
        y = -y;
    }
    if (v < 0) {
        v += abs(m) / y;
    }
    return make_pair(v, y);
}

template<unsigned_integral T>
constexpr pair<T, T> inv_gcd(T x, T m) {
    using U = make_signed_t<T>;
    return inv_gcd(U(x), U(m));
}

template<integral T>
constexpr T inv(T x, T m) {
    assert(0 < x && x < m);
    auto [a, g] = inv_gcd(x, m);
    assert(g == 1);
    return a;
}

}  // namespace cplib

#endif  // CPLIB_INV_HPP
