#ifndef CPLIB_POLYNOMIAL_HPP
#define CPLIB_POLYNOMIAL_HPP 1

#include "cplib/ntt.hpp"

namespace cplib {

template<typename mint>
    requires (is_static_modint_v<mint>)
struct polynomial : public vector<mint> {
    using poly = polynomial;
    polynomial() : polynomial(1) {
    }
    explicit polynomial(size_t n) : vector<mint>(n) {
    }
    polynomial(const vector<mint> &v) : vector<mint>(v) {
    }
    polynomial(vector<mint> &&v) : vector<mint>(v) {
    }
    polynomial(initializer_list<mint> l) : vector<mint>(l) {
    }
    template<input_iterator It>
    polynomial(It first, It last) : vector<mint>(first, last) {
    }
    template<typename F>
        requires (is_convertible_v<F, function<mint(int)>>)
    polynomial(size_t n, F f) : vector<mint>(n) {
        for (size_t i = 0; i < n; ++i) {
            (*this)[i] = f(int(i));
        }
    }
    poly operator+() const {
        return *this;
    }
    poly operator-() const {
        poly t = *this;
        for (mint &x : t) {
            x = -x;
        }
        return t;
    }
    poly &operator+=(const poly &o) {
        if (this->size() < o.size()) {
            this->resize(o.size());
        }
        for (size_t i = 0; i < o.size(); ++i) {
            (*this)[i] += o[i];
        }
        return *this;
    }
    poly &operator-=(const poly &o) {
        return *this += -o;
    }
    poly &operator*=(const poly &o) {
        *this = convolve(*this, o);
        return *this;
    }
    poly &operator*=(mint v) {
        for (size_t i = 0; i < this->size(); ++i) {
            (*this)[i] *= v;
        }
        return *this;
    }
    poly &operator/=(const poly &o) {
        if (this->size() < o.size()) {
            this->assign(1, mint(0));
            return *this;
        }
        poly t = o;
        reverse(this->begin(), this->end());
        reverse(t.begin(), t.end());
        size_t ns = this->size() + 1 - t.size();
        t.resize(ns);
        *this *= inv(t);
        this->resize(ns);
        reverse(this->begin(), this->end());
        return *this;
    }
    poly &operator/=(mint v) {
        return *this *= inv(v);
    }
    poly &operator%=(const poly &o) {
        if (this->size() < o.size()) {
            return *this;
        }
        poly t = (*this / o) * o;
        this->resize(o.size() - 1);
        for (size_t i = 0; i < this->size(); ++i) {
            (*this)[i] -= t[i];
        }
        return *this;
    }
    poly trunc(size_t n) const {
        poly t = *this;
        t.resize(n);
        return t;
    }
    friend poly operator+(const poly &a, const poly &b) {
        poly t = a;
        return t += b;
    }
    friend poly operator-(const poly &a, const poly &b) {
        poly t = a;
        return t -= b;
    }
    friend poly operator*(const poly &a, const poly &b) {
        return convolve(a, b);
    }
    friend poly operator*(const poly &a, mint v) {
        poly t = a;
        return t *= v;
    }
    friend poly operator*(mint v, const poly &a) {
        poly t = a;
        return t *= v;
    }
    friend poly operator/(const poly &a, const poly &b) {
        poly t = a;
        return t /= b;
    }
    friend poly operator/(const poly &a, mint v) {
        poly t = a;
        return t /= v;
    }
    friend poly operator%(const poly &a, const poly &b) {
        poly t = a;
        return t %= b;
    }
};

template<typename T>
struct is_polynomial : public false_type {
};

template<typename mint>
    requires (is_static_modint_v<mint>)
struct is_polynomial<polynomial<mint>> : public true_type {
};

template<typename T>
constexpr bool is_polynomial_v = is_polynomial<T>::value;

template<typename poly>
    requires (is_polynomial_v<poly>)
poly deriv(const poly &a) {
    if (a.size() == 1) {
        return poly{0};
    }
    poly c(a.size() - 1);
    for (size_t i = 1; i < a.size(); ++i) {
        c[i - 1] = a[i] * i;
    }
    return c;
}

template<typename poly>
    requires (is_polynomial_v<poly>)
poly integ(const poly &a) {
    poly c(a.size() + 1);
    for (size_t i = 0; i < a.size(); ++i) {
        c[i + 1] = a[i] / (i + 1);
    }
    return c;
}

template<typename poly>
    requires (is_polynomial_v<poly>)
poly inv(const poly &a) {
    assert(a[0] != 0);
    poly c = {1 / a[0]};
    while (c.size() < a.size()) {
        c.resize(c.size() << 1);
        poly t = c * c * a.trunc(min(a.size(), c.size()));
        for (size_t i = c.size() >> 1; i < min(t.size(), c.size()); ++i) {
            c[i] = -t[i];
        }
    }
    c.resize(a.size());
    return c;
}

template<typename poly>
    requires (is_polynomial_v<poly>)
poly sqrt(const poly &a) {
    assert(a[0] == 1);
    static const auto inv2 = inv(typename poly::value_type(2));
    poly c = {1};
    while (c.size() < a.size()) {
        c.resize(c.size() << 1);
        poly t = a.trunc(min(a.size(), c.size())) * inv(c);
        for (size_t i = c.size() >> 1; i < min(t.size(), c.size()); ++i) {
            c[i] = inv2 * t[i];
        }
    }
    c.resize(a.size());
    return c;
}

template<typename poly>
    requires (is_polynomial_v<poly>)
poly log(const poly &a) {
    return integ(deriv(a) * inv(a)).trunc(a.size());
}

template<typename poly>
    requires (is_polynomial_v<poly>)
poly exp(const poly &a) {
    assert(a[0] == 0);
    poly c = {1};
    while (c.size() < a.size()) {
        poly t = c;
        c.resize(c.size() << 1);
        t *= a.trunc(min(a.size(), c.size())) + poly{1} - log(c);
        for (size_t i = c.size() >> 1; i < min(t.size(), c.size()); ++i) {
            c[i] = t[i];
        }
    }
    c.resize(a.size());
    return c;
}

}  // namespace cplib

#endif  // CPLIB_POLYNOMIAL_HPP
