#ifndef CPLIB_FFT_HPP
#define CPLIB_FFT_HPP 1

#include "cplib/bit.hpp"

namespace cplib {

template<floating_point T>
struct fft_info {
    static constexpr T PI = numbers::pi_v<T>;
    int k;
    vector<int> rev;
    vector<complex<T>> roots;
    fft_info() : k(1), rev{0, 1}, roots{0, 1} {
    }
    int ensure(int nk) {
        if (k >= nk) {
            return k - nk;
        }
        rev.resize(1 << nk);
        roots.resize(1 << nk);
        for (int i = 0; i < (1 << nk); ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nk - 1));
        }
        for (; k < nk; ++k) {
            T ang = PI / (1 << k);
            complex<T> w(cos(ang), sin(-ang));
            for (int i = (1 << (k - 1)); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * w;
            }
        }
        return 0;
    }
};

template<floating_point T>
void fft(vector<complex<T>> &a) {
    int n = int(a.size());
    assert(ispow2(n));
    static fft_info<T> info = {};
    int ofs = info.ensure(ctz(n));
    for (int i = 0; i < n; ++i) {
        if (i < (info.rev[i] >> ofs)) {
            swap(a[i], a[info.rev[i] >> ofs]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = i; j < i + k; ++j) {
                complex<T> t = info.roots[k + j - i] * a[j + k];
                a[j + k] = a[j] - t;
                a[j] += t;
            }
        }
    }
}

template<floating_point T>
vector<T> convolve(const vector<T> &a, const vector<T> &b) {
    assert(!a.empty());
    assert(!b.empty());
    int n = int(a.size() + b.size()) - 1;
    int m = ceil2(n);
    vector<complex<T>> c(m);
    for (int i = 0; i < m; ++i) {
        T x = (i < int(a.size()) ? a[i] : 0);
        T y = (i < int(b.size()) ? b[i] : 0);
        c[i] = complex<T>(x, y);
    }
    fft(c);
    const T inv_m = T(1) / m;
    for (int i = 0; i < m; ++i) {
        c[i] *= c[i] * inv_m;
    }
    reverse(c.begin() + 1, c.end());
    fft(c);
    vector<T> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = c[i].imag() * 0.5;
    }
    return res;
}

template<integral T>
vector<T> convolve(const vector<T> &a, const vector<T> &b) {
    assert(!a.empty());
    assert(!b.empty());
    vector<double> d = convolve(vector<double>(a.begin(), a.end()),
                                vector<double>(b.begin(), b.end()));
    int n = int(d.size());
    vector<T> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = T(d[i] + 0.5);
    }
    return c;
}

}  // namespace cplib

#endif  // CPLIB_FFT_HPP
