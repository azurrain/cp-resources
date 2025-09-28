#ifndef CPLIB_SAFE_MOD_HPP
#define CPLIB_SAFE_MOD_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<signed_integral T, signed_integral U>
constexpr U safe_mod(T x, U m) {
    assert(m > 0);
    x %= m;
    if (x < 0) {
        x += m;
    }
    return U(x);
}

}  // namespace cplib

#endif  // CPLIB_SAFE_MOD_HPP
