#ifndef CPLIB_MODINT_BASE_HPP
#define CPLIB_MODINT_BASE_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct modint_base {
};

template<typename T>
struct is_modint : public is_base_of<modint_base, T> {
};

template<typename T>
constexpr bool is_modint_v = is_modint<T>::value;

}  // namespace cplib

#endif  // CPLIB_MODINT_BASE_HPP
