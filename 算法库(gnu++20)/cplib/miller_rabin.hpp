#ifndef CPLIB_MILLER_RABIN_HPP
#define CPLIB_MILLER_RABIN_HPP 1

#include "cplib/power.hpp"

namespace cplib {

constexpr bool is_prime(int n) {
    if (n == 2 || n == 7 || n == 61) {
        return true;
    }
    if (n <= 1 || n % 2 == 0) {
        return false;
    }
    int d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    constexpr array<int, 3> bases = {2, 7, 61};
    for (int a : bases) {
        int t = d;
        int r = power(a, t, n);
        while (t != n - 1 && r != 1 && r != n - 1) {
            r = int(ll(r) * ll(r) % n);
            t <<= 1;
        }
        if (r != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

}  // namespace cplib

#endif  // CPLIB_MILLER_RABIN_HPP
