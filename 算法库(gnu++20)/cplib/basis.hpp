#ifndef CPLIB_BASIS_HPP
#define CPLIB_BASIS_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename T, size_t N> requires (sizeof(T) * CHAR_BIT >= N)
struct basis : public array<T, N> {
    basis() : array<T, N>{} {
    }
    bool insert(T x) {
        for (int i = N - 1; i != -1; --i) {
            if ((x >> i & 1) == 0) {
                continue;
            }
            if ((*this)[i] == 0) {
                (*this)[i] = x;
                return true;
            }
            x ^= (*this)[i];
        }
        return false;
    }
    bool check(T x) const {
        for (int i = N - 1; i != -1; --i) {
            if ((x >> i & 1) == 0) {
                continue;
            }
            if ((*this)[i] == 0) {
                return false;
            }
            x ^= (*this)[i];
        }
        return true;
    }
};

}  // namespace cplib

#endif  // CPLIB_BASIS_HPP
