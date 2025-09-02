#ifndef CPLIB_KMP_HPP
#define CPLIB_KMP_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename Cont>
vector<int> kmp(const Cont &s) {
    int n = int(s.size());
    vector<int> pi(n);
    int j = 0;
    for (int i = 1; i < n; ++i) {
        while (j != 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

}  // namespace cplib

#endif  // CPLIB_KMP_HPP
