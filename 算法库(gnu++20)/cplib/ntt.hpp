#ifndef CPLIB_NTT_HPP
#define CPLIB_NTT_HPP 1

#include "cplib/bit.hpp"
#include "cplib/miller_rabin.hpp"
#include "cplib/static_modint.hpp"

namespace cplib {

constexpr int find_ntt_root(int m) {
    assert(is_prime(m));
    int g = 2;
    while (power(g, (m - 1) >> 1, m) == 1) {
        ++g;
    }
    return power(g, (m - 1) >> ctz(m - 1), m);
}

template<typename mint>
    requires (is_static_modint_v<mint> && is_prime(mint::getm()))
struct ntt_info {
    static constexpr int M = mint::getm();
    static constexpr int K = ctz(M - 1);
    static constexpr int G = find_ntt_root(M);
    int k;
    vector<int> rev;
    vector<mint> roots;
    ntt_info() : k(1), rev{0, 1}, roots{0, 1} {
    }
    int ensure(int nk) {
        assert(nk <= K);
        if (k >= nk) {
            return k - nk;
        }
        rev.resize(1 << nk);
        roots.resize(1 << nk);
        for (int i = 0; i < (1 << nk); ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nk - 1));
        }
        for (; k < nk; ++k) {
            mint w = power(G, 1 << (K - k - 1), M);
            for (int i = (1 << (k - 1)); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * w;
            }
        }
        return 0;
    }
};

template<typename mint>
    requires (is_static_modint_v<mint> && is_prime(mint::getm()))
void ntt(vector<mint> &a) {
    int n = int(a.size());
    assert(ispow2(n));
    static ntt_info<mint> info = {};
    int ofs = info.ensure(ctz(n));
    for (int i = 0; i < n; ++i) {
        if (i < (info.rev[i] >> ofs)) {
            swap(a[i], a[info.rev[i] >> ofs]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = i; j < i + k; ++j) {
                mint t = info.roots[k + j - i] * a[j + k];
                a[j + k] = a[j] - t;
                a[j] += t;
            }
        }
    }
}

template<typename mint>
    requires (is_static_modint_v<mint>)
vector<mint> convolve(vector<mint> a, vector<mint> b) {
    assert(!a.empty());
    assert(!b.empty());
    int n = int(a.size() + b.size()) - 1;
    int m = ceil2(n);
    a.resize(m);
    b.resize(m);
    ntt(a);
    ntt(b);
    const mint inv_m = inv(mint(m));
    for (int i = 0; i < m; ++i) {
        a[i] *= b[i] * inv_m;
    }
    reverse(a.begin() + 1, a.end());
    ntt(a);
    a.resize(n);
    return a;
}

}  // namespace cplib

#endif  // CPLIB_NTT_HPP
