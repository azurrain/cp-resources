#ifndef CPLIB_NTT_HPP
#define CPLIB_NTT_HPP 1

#include "cplib/power.hpp"
#include "cplib/bit.hpp"
#include "cplib/static_modint.hpp"
#include "cplib/hash_map.hpp"

namespace cplib {

template<integral T>
constexpr T find_ntt_root(T m) {
    assert(m >= 3 && (m & 1));
    T x = 2;
    while (power(x, (m - 1) >> 1, m) == 1) {
        ++x;
    }
    assert(power(x, m - 1, m) == 1);
    return x;
}

template<typename mint, bool INV> requires (is_static_modint_v<mint>)
void ntt(vector<mint> &a) {
    static constexpr mint R = find_ntt_root(mint::getm());
    static constexpr mint C = (INV ? inv(R) : R);
    static int m = 0;
    static vector<int> rev = {};
    int n = int(a.size());
    assert((n & (n - 1)) == 0);
    if (m < n) {
        m = n;
        rev.resize(m);
        for (int i = 0; i < m; ++i) {
            rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (m >> 1);
        }
    }
    int shift = 0;
    while ((n << shift) < m) {
        ++shift;
    }
    for (int i = 0; i < n; ++i) {
        if (i < (rev[i] >> shift)) {
            swap(a[i], a[rev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        mint wn = power(C, (mint::getm() - 1) >> (ilog2(k) + 1));
        for (int i = 0; i < n; i += k << 1) {
            mint w = 1;
            for (int j = i; j < i + k; ++j) {
                mint g = a[j];
                mint h = w * a[j + k];
                a[j] = g + h;
                a[j + k] = g - h;
                w *= wn;
            }
        }
    }
    if constexpr (INV) {
        mint inv_n = inv(mint(n));
        for (mint &x : a) {
            x *= inv_n;
        }
    }
}

template<typename mint> requires (is_static_modint_v<mint>)
vector<mint> convolve(vector<mint> a, vector<mint> b) {
    assert(!a.empty());
    assert(!b.empty());
    int n = int(a.size() + b.size()) - 1;
    int m = ceil2(n);
    a.resize(m);
    b.resize(m);
    ntt<mint, false>(a);
    ntt<mint, false>(b);
    vector<mint> c(m);
    for (int i = 0; i < m; ++i) {
        c[i] = a[i] * b[i];
    }
    ntt<mint, true>(c);
    c.resize(n);
    return c;
}

}  // namespace cplib

#endif  // CPLIB_NTT_HPP
