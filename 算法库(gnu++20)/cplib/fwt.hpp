#ifndef CPLIB_FWT_HPP
#define CPLIB_FWT_HPP 1

#include "cplib/modint_base.hpp"

namespace cplib {

template<typename mint> requires (is_modint_v<mint>)
void fwt_or(vector<mint> &a, bool inv) {
    int n = int(a.size());
    assert((n & (n - 1)) == 0);
    const mint C = (inv ? -1 : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = i; j < i + k; ++j) {
                a[j + k] += C * a[j];
            }
        }
    }
}

template<typename mint> requires (is_modint_v<mint>)
void fwt_and(vector<mint> &a, bool inv) {
    int n = int(a.size());
    assert((n & (n - 1)) == 0);
    const mint C = (inv ? -1 : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = i; j < i + k; ++j) {
                a[j] += C * a[j + k];
            }
        }
    }
}

template<typename mint> requires (is_modint_v<mint>)
void fwt_xor(vector<mint> &a, bool inv) {
    int n = int(a.size());
    assert((n & (n - 1)) == 0);
    const mint C = (inv ? mint(1) / 2 : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = i; j < i + k; ++j) {
                a[j] += a[j + k];
                a[j + k] = a[j] - 2 * a[j + k];
                a[j] *= C;
                a[j + k] *= C;
            }
        }
    }
}

template<typename mint> requires (is_modint_v<mint>)
vector<mint> convolve(vector<mint> a, vector<mint> b,
                      void (*transform)(vector<mint> &, bool)) {
    int n = int(a.size());
    assert((n & (n - 1)) == 0);
    assert(a.size() == b.size());
    transform(a, false);
    transform(b, false);
    vector<mint> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] * b[i];
    }
    transform(c, true);
    return c;
}

}  // namespace cplib

#endif  // CPLIB_FWT_HPP
