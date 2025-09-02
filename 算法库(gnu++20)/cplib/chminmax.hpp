#ifndef CPLIB_CHMINMAX_HPP
#define CPLIB_CHMINMAX_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename T, typename U>
constexpr bool chmin(T &a, const U &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}
template<typename T, typename U>
constexpr bool chmax(T &a, const U &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

}  // namespace cplib

#endif  // CPLIB_CHMINMAX_HPP
