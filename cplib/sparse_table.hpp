#ifndef CPLIB_SPARSE_TABLE_HPP
#define CPLIB_SPARSE_TABLE_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename T, typename F = function<T(const T &, const T &)>>
struct sparse_table {
    vector<int> lg;
    vector<vector<T>> t;
    F f;
    sparse_table() : lg{}, t{}, f{} {
    }
    sparse_table(const vector<T> &a, const F &f = {})
        : lg(a.size()), t{}, f(f) {
        int n = int(a.size());
        if (n == 0) {
            return;
        }
        for (int i = 1; i < n; ++i) {
            lg[i] = lg[(i - 1) >> 1] + 1;
        }
        t.resize(lg[n - 1] + 1);
        t[0] = a;
        for (int i = 1; i <= lg[n - 1]; ++i) {
            t[i].resize(n - (1 << i) + 1);
            for (int j = 0; j <= n - (1 << i); ++j) {
                t[i][j] = f(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) const {
        assert(l <= r);
        int s = lg[r - l];
        return f(t[s][l], t[s][r - (1 << s) + 1]);
    }
};

}  // namespace cplib

#endif  // CPLIB_SPARSE_TABLE_HPP
