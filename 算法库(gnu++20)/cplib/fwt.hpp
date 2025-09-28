#ifndef CPLIB_FWT_HPP
#define CPLIB_FWT_HPP 1

#include "cplib/modint_base.hpp"

namespace cplib {

template<typename mint, bool INV>
    requires (is_modint_v<mint>)
void fwt_and(vector<mint> &a) {
    int n = int(a.size());
    assert(ispow2(n));
    const mint C = (INV ? -1 : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = i; j < i + k; ++j) {
                a[j] += C * a[j + k];
            }
        }
    }
}

template<typename mint, bool INV>
    requires (is_modint_v<mint>)
void fwt_or(vector<mint> &a) {
    int n = int(a.size());
    assert(ispow2(n));
    const mint C = (INV ? -1 : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = i; j < i + k; ++j) {
                a[j + k] += C * a[j];
            }
        }
    }
}

template<typename mint, bool INV>
    requires (is_modint_v<mint>)
void fwt_xor(vector<mint> &a) {
    int n = int(a.size());
    assert(ispow2(n));
    const mint C = (INV ? inv(mint(2)) : 1);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = i; j < i + k; ++j) {
                a[j] += a[j + k];
                a[j + k] = a[j] - 2 * a[j + k];
                a[j] *= C;
                a[j + k] *= C;
            }
        }
    }
}

enum struct fwt {
    AND = 0,
    OR = 1,
    XOR = 2,
};

template<typename mint>
    requires (is_modint_v<mint>)
vector<mint> convolve(vector<mint> a, vector<mint> b, fwt id) {
    static constexpr array<void (*)(vector<mint> &), 6> t = {
        fwt_and<mint, false>,
        fwt_and<mint, true>,
        fwt_or<mint, false>,
        fwt_or<mint, true>,
        fwt_xor<mint, false>,
        fwt_xor<mint, true>,
    };
    int n = int(a.size());
    assert(ispow2(n));
    assert(a.size() == b.size());
    t[2 * int(id)](a);
    t[2 * int(id)](b);
    vector<mint> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] * b[i];
    }
    t[2 * int(id) + 1](c);
    return c;
}

}  // namespace cplib

#endif  // CPLIB_FWT_HPP
