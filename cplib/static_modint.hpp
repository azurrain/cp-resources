#ifndef CPLIB_STATIC_MODINT_HPP
#define CPLIB_STATIC_MODINT_HPP 1

#include "cplib/i128.hpp"
#include "cplib/inv.hpp"
#include "cplib/modint_base.hpp"

namespace cplib {

template<integral T, T M> requires (M > 0)
struct static_modint : public modint_base {
    using mint = static_modint;
    using value_type = T;
    static constexpr T getm() {
        return M;
    }
    constexpr static_modint() : v(0) {
    }
    template<typename U>
    constexpr static_modint(U x)
        : v(T(x % getm()) + (x < 0 ? getm() : 0)) {
    }
    constexpr static_modint(bool x) : v(T(x) % getm()) {
    }
    template<typename U>
    explicit constexpr operator U() const {
        return U(v);
    }
    constexpr mint operator+() const {
        return *this;
    }
    constexpr mint operator-() const {
        return mint(getm() - v);
    }
    constexpr mint &operator++() {
        v = (v + 1 == getm() ? 0 : v + 1);
        return *this;
    }
    constexpr mint operator++(int) {
        mint t = *this;
        ++*this;
        return t;
    }
    constexpr mint &operator--() {
        v = (v == 0 ? getm() - 1 : v - 1);
        return *this;
    }
    constexpr mint operator--(int) {
        mint t = *this;
        --*this;
        return t;
    }
    constexpr mint &operator+=(mint o) {
        v += (v >= getm() - o.v ? o.v - getm() : o.v);
        return *this;
    }
    constexpr mint &operator-=(mint o) {
        return *this += -o;
    }
    constexpr mint &operator*=(mint o) {
        if constexpr (2 * sizeof(T) <= sizeof(ull)) {
            v = T(ull(v) * ull(o.v) % getm());
        } else {
            v = T(u128(v) * u128(o.v) % getm());
        }
        return *this;
    }
    constexpr mint &operator/=(mint o) {
        return *this *= inv(o);
    }
    friend constexpr mint operator+(mint x, mint y) {
        return x += y;
    }
    friend constexpr mint operator-(mint x, mint y) {
        return x -= y;
    }
    friend constexpr mint operator*(mint x, mint y) {
        return x *= y;
    }
    friend constexpr mint operator/(mint x, mint y) {
        return x /= y;
    }
    friend constexpr bool operator==(mint x, mint y) {
        return x.v == y.v;
    }
    friend constexpr bool operator!=(mint x, mint y) {
        return x.v != y.v;
    }
    friend istream &operator>>(istream &is, mint &x) {
        is >> x.v;
        x = mint(x.v);
        return is;
    }
    friend ostream &operator<<(ostream &os, mint x) {
        return os << x.v;
    }

private:
    T v;
};

template<typename T>
struct is_static_modint : public false_type {
};

template<integral T, T M>
struct is_static_modint<static_modint<T, M>> : public true_type {
};

template<typename T>
constexpr bool is_static_modint_v = is_static_modint<T>::value;

template<typename mint> requires (is_static_modint_v<mint>)
constexpr mint inv(mint x) {
    return mint(inv(typename mint::value_type(x), mint::getm()));
}

}  // namespace cplib

#endif  // CPLIB_STATIC_MODINT_HPP
