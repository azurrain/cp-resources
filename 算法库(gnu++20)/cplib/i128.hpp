#ifndef CPLIB_I128_HPP
#define CPLIB_I128_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

using i128 = __int128;
using u128 = unsigned __int128;

ostream &operator<<(ostream &os, i128 x) {
    static char s[41];
    int p = 40;
    int sgn = (x < 0);
    do {
        s[--p] = char('0' + (sgn == 1 ? -(x % 10) : x % 10));
        x /= 10;
    } while (x);
    if (sgn == 1) {
        s[--p] = '-';
    }
    return os << (s + p);
}

ostream &operator<<(ostream &os, u128 x) {
    static char s[40];
    int p = 39;
    do {
        s[--p] = char('0' + x % 10);
        x /= 10;
    } while (x);
    return os << (s + p);
}

}  // namespace cplib

#endif  // CPLIB_I128_HPP
