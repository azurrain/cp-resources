#ifndef CPLIB_DYNAMIC_MODINT_HPP
#define CPLIB_DYNAMIC_MODINT_HPP 1

#include "cplib/i128.hpp"
#include "safe_mod.hpp"
#include "cplib/inv.hpp"
#include "cplib/modint_base.hpp"

namespace cplib {

struct barrett {
    explicit barrett(int m) : m(uint(m)), im(UINT64_MAX / m + 1) {
    }
    int getm() const {
        return int(m);
    }
    int mul(int a, int b) const {
        ull c = ull(a) * ull(b);
        c -= ull((u128(c) * im) >> 64) * m;
        if (c >= m) {
            c += m;
        }
        return int(c);
    }

private:
    uint m;
    u128 im;
};

template<int ID>
struct dynamic_modint : public modint_base {
    using mint = dynamic_modint;
    static int getm() {
        return bt.getm();
    }
    static void setm(int m) {
        assert(m > 0);
        bt = barrett(m);
    }
    constexpr dynamic_modint() : v(0) {
    }
    template<signed_integral T>
    dynamic_modint(T x) : v(safe_mod(x, getm())) {
    }
    template<unsigned_integral T>
    dynamic_modint(T x) : v(int(x % getm())) {
    }
    dynamic_modint(bool x) : v(int(x) % getm()) {
    }
    template<typename T>
    explicit constexpr operator T() const {
        return T(v);
    }
    constexpr mint operator+() const {
        return *this;
    }
    mint operator-() const {
        return mint(getm() - v);
    }
    mint &operator++() {
        v = (v + 1 == getm() ? 0 : v + 1);
        return *this;
    }
    mint operator++(int) {
        mint t = *this;
        ++*this;
        return t;
    }
    mint &operator--() {
        v = (v == 0 ? getm() - 1 : v - 1);
        return *this;
    }
    mint operator--(int) {
        mint t = *this;
        --*this;
        return t;
    }
    mint &operator+=(mint o) {
        v += (v >= getm() - o.v ? o.v - getm() : o.v);
        return *this;
    }
    mint &operator-=(mint o) {
        return *this += -o;
    }
    mint &operator*=(mint o) {
        v = bt.mul(v, o.v);
        return *this;
    }
    mint &operator/=(mint o) {
        return *this *= inv(o);
    }
    friend mint operator+(mint x, mint y) {
        return x += y;
    }
    friend mint operator-(mint x, mint y) {
        return x -= y;
    }
    friend mint operator*(mint x, mint y) {
        return x *= y;
    }
    friend mint operator/(mint x, mint y) {
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
    static barrett bt;
    int v;
};
template<int ID>
barrett dynamic_modint<ID>::bt(INT_MAX);

template<typename T>
struct is_dynamic_modint : public false_type {
};

template<int ID>
struct is_dynamic_modint<dynamic_modint<ID>> : public true_type {
};

template<typename T>
constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

template<typename mint>
    requires (is_dynamic_modint_v<mint>)
constexpr mint inv(mint x) {
    return mint(inv(int(x), mint::getm()));
}

}  // namespace cplib

#endif  // CPLIB_DYNAMIC_MODINT_HPP
