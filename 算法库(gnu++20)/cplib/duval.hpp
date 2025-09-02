#ifndef CPLIB_DUVAL_HPP
#define CPLIB_DUVAL_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename T>
vector<int> duval(const T &s) {
    int n = int(s.size());
    int i = 0;
    vector<int> pos;
    while (i < n) {
        int j = i;
        int k = i + 1;
        while (k < n && s[j] <= s[k]) {
            j = (s[j] < s[k] ? i : j + 1);
            ++k;
        }
        while (i <= j) {
            pos.push_back(i);
            i += k - j;
        }
    }
    return pos;
}

}  // namespace cplib

#endif  // CPLIB_DUVAL_HPP
