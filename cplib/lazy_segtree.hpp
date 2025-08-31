#ifndef CPLIB_LAZY_SEGTREE_HPP
#define CPLIB_LAZY_SEGTREE_HPP 1

#include "cplib/bit.hpp"

namespace cplib {

template<typename Info, typename Lazy>
struct lazy_segtree {
    int n;
    int m;
    int h;
    vector<Info> d;
    vector<Lazy> t;
    lazy_segtree() : lazy_segtree(0) {
    }
    explicit lazy_segtree(int n) : n(n), m(ceil2(n)), h(ilog2(m)), d(2 * m), t(m) {
    }
    template<typename T>
    explicit lazy_segtree(const vector<T> &a)
        : n(int(a.size())), m(ceil2(n)), h(ilog2(m)), d(2 * m), t(m) {
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
        for (int i = h; i > 0; --i) {
            push(p >> i);
        }
        d[p] = s;
        for (int i = 1; i <= h; ++i) {
            pull(p >> i);
        }
    }
    Info get(int p) {
        assert(0 <= p && p < n);
        p += m;
        for (int i = h; i > 0; --i) {
            push(p >> i);
        }
        return d[p];
    }
    Info query(int l, int r) {
        assert(0 <= l && l <= r + 1 && r < n);
        l += m;
        r += m;
        for (int i = h; i > 0; --i) {
            if (l >> i << i != l) {
                push(l >> i);
            }
            if ((r + 1) >> i << i != r + 1) {
                push(r >> i);
            }
        }
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
    void apply(int p, const Lazy &f) {
        assert(0 <= p && p < n);
        p += m;
        for (int i = h; i > 0; --i) {
            push(p >> i);
        }
        d[p].apply(f);
        for (int i = 1; i <= h; ++i) {
            pull(p >> i);
        }
    }
    void apply(int l, int r, const Lazy &f) {
        assert(0 <= l && l <= r + 1 && r < n);
        l += m;
        r += m;
        for (int i = h; i > 0; --i) {
            if (l >> i << i != l) {
                push(l >> i);
            }
            if ((r + 1) >> i << i != r + 1) {
                push(r >> i);
            }
        }
        int l2 = l;
        int r2 = r;
        while (l <= r) {
            if (l & 1) {
                node_apply(l++, f);
            }
            if (~r & 1) {
                node_apply(r--, f);
            }
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;
        for (int i = 1; i <= h; ++i) {
            if (l >> i << i != l) {
                pull(l >> i);
            }
            if ((r + 1) >> i << i != r + 1) {
                pull(r >> i);
            }
        }
    }
    template<typename G>
    int min_r(int l, const G &g) {
        assert(0 <= l && l <= n);
        if (l == n) {
            return n;
        }
        l += m;
        for (int i = h; i > 0; --i) {
            push(l >> i);
        }
        Info s = {};
        do {
            while (~l & 1) {
                l >>= 1;
            }
            if (g(s + d[l])) {
                while (l < m) {
                    push(l);
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
    int max_l(int r, const G &g) {
        assert(-1 <= r && r < n);
        if (r == -1) {
            return -1;
        }
        r += m;
        for (int i = h; i > 0; --i) {
            push(r >> i);
        }
        Info s = {};
        do {
            while ((r & 1) && r > 1) {
                r >>= 1;
            }
            if (g(d[r] + s)) {
                while (r < m) {
                    push(r);
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
    void node_apply(int p, const Lazy &f) {
        d[p].apply(f);
        if (p < m) {
            t[p].apply(f);
        }
    }
    void push(int p) {
        node_apply(2 * p, t[p]);
        node_apply(2 * p + 1, t[p]);
        t[p] = Lazy{};
    }
};

}  // namespace cplib

#endif  // CPLIB_LAZY_SEGTREE_HPP
