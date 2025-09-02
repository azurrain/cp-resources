#ifndef CPLIB_SEGTREE_HPP
#define CPLIB_SEGTREE_HPP 1

#include "cplib/bit.hpp"

namespace cplib {

template<typename Info>
struct segtree {
    int n;
    int m;
    vector<Info> d;
    segtree() : segtree(0) {
    }
    explicit segtree(int n) : n(n), m(ceil2(n)), d(2 * m) {
    }
    template<typename T>
    explicit segtree(const vector<T> &a) : n(int(a.size())), m(ceil2(n)), d(2 * m) {
        for (int i = 0; i < n; ++i) {
            d[m + i] = Info(a[i]);
        }
        for (int i = m - 1; i > 0; --i) {
            pull(i);
        }
    }
    void set(int p, const Info &s) {
        assert(0 <= p && p < n);
        p += m;
        d[p] = s;
        while (p >>= 1) {
            pull(p);
        }
    }
    Info get(int p) const {
        assert(0 <= p && p < n);
        return d[p + m];
    }
    Info query(int l, int r) const {
        assert(0 <= l && l <= r + 1 && r < n);
        l += m;
        r += m;
        Info sl = {};
        Info sr = {};
        while (l <= r) {
            if (l & 1) {
                sl = sl + d[l++];
            }
            if (~r & 1) {
                sr = d[r--] + sr;
            }
            l >>= 1;
            r >>= 1;
        }
        return sl + sr;
    }
    Info all() const {
        return d[1];
    }
    template<typename G>
    int min_r(int l, const G &g) const {
        assert(0 <= l && l <= n);
        if (l == n) {
            return n;
        }
        l += m;
        Info s = {};
        do {
            while (~l & 1) {
                l >>= 1;
            }
            if (g(s + d[l])) {
                while (l < m) {
                    l <<= 1;
                    if (!g(s + d[l])) {
                        s = s + d[l++];
                    }
                }
                return l - m;
            }
            s = s + d[l++];
        } while (l & (l - 1));
        return n;
    }
    template<typename G>
    int max_l(int r, const G &g) const {
        assert(-1 <= r && r < n);
        if (r == -1) {
            return -1;
        }
        r += m;
        Info s = {};
        do {
            while ((r & 1) && r > 1) {
                r >>= 1;
            }
            if (g(d[r] + s)) {
                while (r < m) {
                    r = r << 1 | 1;
                    if (!g(d[r] + s)) {
                        s = d[r--] + s;
                    }
                }
                return r - m;
            }
            s = d[r--] + s;
        } while (r & (r + 1));
        return -1;
    }
    void pull(int p) {
        d[p] = d[2 * p] + d[2 * p + 1];
    }
};

}  // namespace cplib

#endif  // CPLIB_SEGTREE_HPP
