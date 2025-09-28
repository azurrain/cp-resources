#ifndef CPLIB_DSU_HPP
#define CPLIB_DSU_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct dsu {
    int n;
    vector<int> f;
    dsu() : dsu(0) {
    }
    explicit dsu(int n) : n(n), f(n, -1) {
    }
    int leader(int x) {
        assert(0 <= x && x < n);
        return f[x] < 0 ? x : (f[x] = leader(f[x]));
    }
    bool merge(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        x = leader(x);
        y = leader(y);
        if (x == y) {
            return false;
        }
        if (-f[x] > -f[y]) {
            swap(x, y);
        }
        f[y] += f[x];
        f[x] = y;
        return true;
    }
    bool same(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        return leader(x) == leader(y);
    }
    int size(int x) {
        assert(0 <= x && x < n);
        return -f[leader(x)];
    }
    vector<vector<int>> groups() {
        vector<int> buf(n);
        vector<int> siz(n);
        for (int i = 0; i < n; ++i) {
            buf[i] = leader(i);
            ++siz[buf[i]];
        }
        vector<vector<int>> res(n);
        for (int i = 0; i < n; ++i) {
            res[i].reserve(siz[i]);
        }
        for (int i = 0; i < n; ++i) {
            res[buf[i]].push_back(i);
        }
        res.erase(remove_if(res.begin(), res.end(),
                            [](const vector<int> &v) { return v.empty(); }),
                  res.end());
        return res;
    }
};

}  // namespace cplib

#endif  // CPLIB_DSU_HPP
