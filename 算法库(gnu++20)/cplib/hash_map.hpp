#ifndef CPLIB_HASH_MAP_HPP
#define CPLIB_HASH_MAP_HPP 1

#include <ext/pb_ds/assoc_container.hpp>

#include "cplib/i128.hpp"
#include "cplib/rng.hpp"

namespace cplib {

struct splitmix64 {
    static const ull RND;
    template<integral T>
    size_t operator()(T x) const {
        ull y = ull(x) + RND + 0x9e3779b97f4a7c15ULL;
        y = (y ^ (y >> 30)) * 0xbf58476d1ce4e5b9ULL;
        y = (y ^ (y >> 27)) * 0x94d049bb133111ebULL;
        return size_t(y ^ (y >> 31));
    }
};
const ull splitmix64::RND = rng();

struct hash61 {
    static constexpr ull M = (1ULL << 61) - 1;
    static const ull B;
    static constexpr ull add(ull a, ull b) {
        a += b;
        if (a >= M) {
            a -= M;
        }
        return a;
    }
    static constexpr ull mul(ull a, ull b) {
        u128 c = u128(a) * u128(b);
        c = (c & M) + (c >> 61);
        if (c >= M) {
            c -= M;
        }
        return ull(c);
    }
    template<ranges::range Cont>
    size_t operator()(const Cont &s) const {
        ull v = 0;
        for (auto &&x : s) {
            v = add(mul(v, B), ull(x));
        }
        return size_t(v);
    }
};
const ull hash61::B = rng() % M;

struct custom_hash {
    template<integral T>
    size_t operator()(T x) const {
        static splitmix64 h;
        return h(x);
    }
    template<ranges::range Cont>
    size_t operator()(const Cont &s) const {
        static hash61 h;
        return h(s);
    }
};

template<typename K, typename V, typename Hash = custom_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;
template<typename K, typename Hash = custom_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

}  // namespace cplib

#endif  // CPLIB_HASH_MAP_HPP
