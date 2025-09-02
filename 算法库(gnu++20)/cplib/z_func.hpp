#ifndef CPLIB_Z_FUNC_HPP
#define CPLIB_Z_FUNC_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename Cont>
vector<int> z_func(const Cont &s) {
    int n = int(s.size());
    vector<int> z(n, n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = i < r ? min(r - i, z[i - l]) : 0;
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

}  // namespace cplib

#endif  // CPLIB_Z_FUNC_HPP
