#ifndef CPLIB_RNG_HPP
#define CPLIB_RNG_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

}  // namespace cplib

#endif  // CPLIB_RNG_HPP
