#ifndef CPLIB_FRAC_HPP
#define CPLIB_FRAC_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<integral T>
struct frac {
    T num;
    T den;
    constexpr frac() : num(0), den(1) {
    }
    constexpr frac(T num) : num(num), den(1) {
    }
    constexpr frac(T num, T den) : num(num), den(den) {
        assert(den != 0);
        simplify();
    }
    explicit constexpr operator bool() const {
        return num;
    }
    template<typename U>
    explicit constexpr operator U() const {
        return U(num) / U(den);
    }
    template<typename U>
    constexpr operator frac<U>() const {
        return frac<U>(num, den);
    }
    constexpr frac operator+() const {
        return *this;
    }
    constexpr frac operator-() const {
        return frac(-num, den);
    }
    constexpr frac &operator+=(const frac &o) {
        num = num * o.den + o.num * den;
        den *= o.den;
        simplify();
        return *this;
    }
    constexpr frac &operator-=(const frac &o) {
        num = num * o.den - o.num * den;
        den *= o.den;
        simplify();
        return *this;
    }
    constexpr frac &operator*=(const frac &o) {
        num *= o.num;
        den *= o.den;
        simplify();
        return *this;
    }
    constexpr frac &operator/=(const frac &o) {
        assert(o.num != 0);
        num *= o.den;
        den *= o.num;
        simplify();
        return *this;
    }
    constexpr void simplify() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        T g = gcd(num, den);
        num /= g;
        den /= g;
    }
    friend constexpr frac operator+(const frac &lhs, const frac &rhs) {
        return frac(lhs) += rhs;
    }
    friend constexpr frac operator-(const frac &lhs, const frac &rhs) {
        return frac(lhs) -= rhs;
    }
    friend constexpr frac operator*(const frac &lhs, const frac &rhs) {
        return frac(lhs) *= rhs;
    }
    friend constexpr frac operator/(const frac &lhs, const frac &rhs) {
        return frac(lhs) /= rhs;
    }
    friend constexpr bool operator<(const frac &lhs, const frac &rhs) {
        return lhs.num * rhs.den < rhs.num * lhs.den;
    }
    friend constexpr bool operator>(const frac &lhs, const frac &rhs) {
        return lhs.num * rhs.den > rhs.num * lhs.den;
    }
    friend constexpr bool operator<=(const frac &lhs, const frac &rhs) {
        return lhs.num * rhs.den <= rhs.num * lhs.den;
    }
    friend constexpr bool operator>=(const frac &lhs, const frac &rhs) {
        return lhs.num * rhs.den >= rhs.num * lhs.den;
    }
    friend constexpr bool operator==(const frac &lhs, const frac &rhs) {
        return lhs.num == rhs.num && lhs.den == rhs.den;
    }
    friend constexpr bool operator!=(const frac &lhs, const frac &rhs) {
        return lhs.num != rhs.num || lhs.den != rhs.den;
    }
    friend ostream &operator<<(ostream &os, const frac &a) {
        return os << a.num << '/' << a.den;
    }
};

}  // namespace cplib

#endif  // CPLIB_FRAC_HPP
