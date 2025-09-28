#ifndef CPLIB_POWER_HPP
#define CPLIB_POWER_HPP 1

#include "cplib/safe_mod.hpp"

namespace cplib {

template<typename T>
constexpr T power(T x, ll n) {
    assert(n >= 0);
    T r = 1;
    while (n) {
        if (n & 1) {
            r *= x;
        }
        x *= x;
        n >>= 1;
    }
    return r;
}

template<integral T>
constexpr int power(T x, ll n, int m) {
    assert(n >= 0);
    assert(m > 0);
    if (m == 1) {
        return 0;
    }
    int y = safe_mod(ll(x), m);
    int r = 1;
    while (n) {
        if (n & 1) {
            r = int(ll(r) * ll(y) % m);
        }
        y = int(ll(y) * ll(y) % m);
        n >>= 1;
    }
    return r;
}

}  // namespace cplib

#endif  // CPLIB_POWER_HPP
