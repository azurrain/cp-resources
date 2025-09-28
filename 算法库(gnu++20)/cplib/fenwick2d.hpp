#ifndef CPLIB_FENWICK2D_HPP
#define CPLIB_FENWICK2D_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename T>
struct fenwick2d {
    int h;
    int w;
    vector<vector<T>> t;
    fenwick2d() : fenwick2d(0, 0) {
    }
    fenwick2d(int h, int w) : h(h), w(w), t(h, vector<T>(w)) {
    }
    void add(int x, int y, T v) {
        assert(0 <= x && x < h);
        assert(0 <= y && y < w);
        for (int i = x; i < h; i |= i + 1) {
            for (int j = y; j < w; j |= j + 1) {
                t[i][j] = t[i][j] + v;
            }
        }
    }
    T get(int x, int y) const {
        assert(-1 <= x && x < h);
        assert(-1 <= y && y < w);
        T s = {};
        for (int i = x; i != -1; i = (i & (i + 1)) - 1) {
            for (int j = y; j != -1; j = (j & (j + 1)) - 1) {
                s = s + t[i][j];
            }
        }
        return s;
    }
    T sum(int x1, int y1, int x2, int y2) const {
        assert(0 <= x1 && x1 <= x2 + 1 && x2 < h);
        assert(0 <= y1 && y1 <= y2 + 1 && y2 < w);
        --x1;
        --y1;
        return get(x2, y2) - get(x2, y1) - get(x1, y2) + get(x1, y1);
    }
};

}  // namespace cplib

#endif  // CPLIB_FENWICK2D_HPP
