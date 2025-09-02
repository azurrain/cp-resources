#ifndef CPLIB_DYNAMIC_MODINT_HPP
#define CPLIB_DYNAMIC_MODINT_HPP 1

#include "cplib/i128.hpp"
#include "cplib/inv.hpp"
#include "cplib/modint_base.hpp"

namespace cplib {

struct barrett {
    uint m;
    u128 im;
    explicit barrett(uint m) : m(m), im(UINT64_MAX / m + 1) {
    }
    uint getm() const {
        return m;
    }
    uint mul(ull a, ull b) const {
        a *= b;
        a -= ull((u128(a) * im) >> 64) * m;
        if (a >= m) {
            a += m;
        }
        return uint(a);
    }
};

template<int ID>
struct dynamic_modint : public modint_base {
    using mint = dynamic_modint;
    using value_type = uint;
    static uint getm() {
        return bt.getm();
    }
    static void setm(uint m) {
        assert(m > 0);
        bt = barrett(m);
    }
    constexpr dynamic_modint() : v(0) {
    }
    template<signed_integral T>
    dynamic_modint(T x) : v(uint(x % ll(getm()) + (x < 0 ? getm() : 0))) {
    }
    template<unsigned_integral T>
    dynamic_modint(T x) : v(uint(x % getm())) {
    }
    dynamic_modint(bool x) : v(uint(x) % getm()) {
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
        x = mint(x.v);
        return is;
    }
    friend ostream &operator<<(ostream &os, mint x) {
        return os << x.v;
    }

private:
    static barrett bt;
    uint v;
};
template<int ID>
barrett dynamic_modint<ID>::bt(UINT32_MAX);

template<typename T>
struct is_dynamic_modint : public false_type {
};

template<int ID>
struct is_dynamic_modint<dynamic_modint<ID>> : public true_type {
};

template<typename T>
constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

template<typename mint> requires (is_dynamic_modint_v<mint>)
constexpr mint inv(mint x) {
    return mint(inv(typename mint::value_type(x), mint::getm()));
}

}  // namespace cplib

#endif  // CPLIB_DYNAMIC_MODINT_HPP
