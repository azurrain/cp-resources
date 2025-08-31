#ifndef CPLIB_FFT_HPP
#define CPLIB_FFT_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<floating_point T>
void fft(vector<complex<T>> &a, bool inv) {
    static const T pi = acos(T(-1));
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
        complex<T> wn(cos(pi / k), sin((inv ? 1 : -1) * pi / k));
        for (int i = 0; i < n; i += k << 1) {
            complex<T> w(1, 0);
            for (int j = i; j < i + k; ++j) {
                complex<T> g = a[j];
                complex<T> h = w * a[j + k];
                a[j] = g + h;
                a[j + k] = g - h;
                w *= wn;
            }
        }
    }
    if (inv) {
        for (complex<T> &x : a) {
            x /= n;
        }
    }
}

template<floating_point T>
vector<T> convolve(const vector<T> &a, const vector<T> &b) {
    assert(!a.empty());
    assert(!b.empty());
    int n = int(a.size() + b.size()) - 1;
    int m = bit_ceil(uint(n));
    vector<complex<T>> ca(m);
    vector<complex<T>> cb(m);
    copy(a.begin(), a.end(), ca.begin());
    copy(b.begin(), b.end(), cb.begin());
    fft(ca, false);
    fft(cb, false);
    vector<complex<T>> cc(m);
    for (int i = 0; i < m; ++i) {
        cc[i] = ca[i] * cb[i];
    }
    fft(cc, true);
    vector<T> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = cc[i].real();
    }
    return c;
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
