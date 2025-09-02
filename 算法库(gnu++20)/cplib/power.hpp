#ifndef CPLIB_POWER_HPP
#define CPLIB_POWER_HPP 1

#include "cplib/i128.hpp"

namespace cplib {

template<typename T>
constexpr T power(T x, ull n) {
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
constexpr T power(T x, ull n, T m) {
    assert(m > 0);
    using U = conditional_t<(2 * sizeof(T) <= sizeof(ull)), ull, u128>;
    T r = 1 % m;
    while (n) {
        if (n & 1) {
            r = T(U(r) * U(x) % m);
        }
        x = T(U(x) * U(x) % m);
        n >>= 1;
    }
    return r;
}

}  // namespace cplib

#endif  // CPLIB_POWER_HPP
