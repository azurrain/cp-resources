#ifndef CPLIB_STATIC_MODINT_HPP
#define CPLIB_STATIC_MODINT_HPP 1

#include "cplib/safe_mod.hpp"
#include "cplib/inv.hpp"
#include "cplib/modint_base.hpp"

namespace cplib {

template<int M>
    requires (M > 0)
struct static_modint : public modint_base {
    using mint = static_modint;
    static constexpr int getm() {
        return M;
    }
    constexpr static_modint() : v(0) {
    }
    template<signed_integral T>
    constexpr static_modint(T x) : v(safe_mod(x, getm())) {
    }
    template<unsigned_integral T>
    constexpr static_modint(T x) : v(int(x % getm())) {
    }
    constexpr static_modint(bool x) : v(int(x) % getm()) {
    }
    template<typename T>
    explicit constexpr operator T() const {
        return T(v);
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
        v = int(ll(v) * ll(o.v) % getm());
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
        x.v = safe_mod(x.v, getm());
        return is;
    }
    friend ostream &operator<<(ostream &os, mint x) {
        return os << x.v;
    }

private:
    int v;
};

template<typename T>
struct is_static_modint : public false_type {
};

template<int M>
struct is_static_modint<static_modint<M>> : public true_type {
};

template<typename T>
constexpr bool is_static_modint_v = is_static_modint<T>::value;

template<typename mint>
    requires (is_static_modint_v<mint>)
constexpr mint inv(mint x) {
    return mint(inv(int(x), mint::getm()));
}

}  // namespace cplib

#endif  // CPLIB_STATIC_MODINT_HPP
