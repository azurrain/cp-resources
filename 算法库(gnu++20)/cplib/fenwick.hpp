#ifndef CPLIB_FENWICK_HPP
#define CPLIB_FENWICK_HPP 1

#include "cplib/bit.hpp"

namespace cplib {

template<typename T>
struct fenwick {
    int n;
    int f2_n;
    vector<T> t;
    fenwick() : fenwick(0) {
    }
    explicit fenwick(int n) : n(n), f2_n(floor2(n)), t(n) {
    }
    explicit fenwick(const vector<T> &a)
        : n(int(a.size())), f2_n(floor2(n)), t(n) {
        partial_sum(a.begin(), a.end(), t.begin());
        for (int i = n - 1; i != -1; --i) {
            int j = (i & (i + 1)) - 1;
            if (j != -1) {
                t[i] = t[i] - t[j];
            }
        }
    }
    void add(int p, T v) {
        assert(0 <= p && p < n);
        while (p < n) {
            t[p] = t[p] + v;
            p |= p + 1;
        }
    }
    T get(int p) const {
        assert(-1 <= p && p < n);
        T s = {};
        while (p != -1) {
            s = s + t[p];
            p = (p & (p + 1)) - 1;
        }
        return s;
    }
    T sum(int l, int r) const {
        assert(0 <= l && l <= r + 1 && r < n);
        return get(r) - get(l - 1);
    }
    int lower_bound(T v) const {
        int p = -1;
        T s = {};
        for (int i = f2_n; i != 0; i >>= 1) {
            if (p + i < n && s + t[p + i] < v) {
                p += i;
                s = s + t[p];
            }
        }
        return p + 1;
    }
};

}  // namespace cplib

#endif  // CPLIB_FENWICK_HPP
