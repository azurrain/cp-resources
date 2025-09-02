#ifndef CPLIB_MANACHER_HPP
#define CPLIB_MANACHER_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename Cont>
vector<int> manacher(const Cont &s) {
    int n = int(s.size());
    if (n == 0) {
        return {};
    }
    vector<int> d(2 * n - 1);
    int l = -1;
    int r = -1;
    for (int c = 0; c < 2 * n - 1; ++c) {
        int i = (c + 1) >> 1;
        int j = c >> 1;
        int k = r < i ? 0 : min(r - j, d[2 * (l + r) - c] >> 1);
        while (k < i && j + k + 1 < n && s[i - k - 1] == s[j + k + 1]) {
            ++k;
        }
        d[c] = 2 * k + 1 - (c & 1);
        if (r < j + k) {
            l = i - k;
            r = j + k;
        }
    }
    return d;
}

}  // namespace cplib

#endif  // CPLIB_MANACHER_HPP
