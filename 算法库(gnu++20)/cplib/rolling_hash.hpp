#ifndef CPLIB_ROLLING_HASH_HPP
#define CPLIB_ROLLING_HASH_HPP 1

#include "cplib/hash_map.hpp"

namespace cplib {

struct rolling_hash {
    static constexpr ull M = hash61::M;
    static const ull B;
    static constexpr ull (*add)(ull, ull) = hash61::add;
    static constexpr ull (*mul)(ull, ull) = hash61::mul;
    static vector<ull> pw;
    int n;
    vector<ull> pf;
    rolling_hash() : n(0), pf{0} {
    }
    ull extend(ull x) {
        ++n;
        pf.push_back(add(mul(pf.back(), B), ull(x)));
        for (int i = int(pw.size()); i <= n; ++i) {
            pw.push_back(mul(pw[i - 1], B));
        }
        return pf.back();
    }
    template<ranges::range Cont>
    ull build(const Cont &s) {
        pf.resize(1);
        pf.reserve(s.size() + 1);
        for (auto &&x : s) {
            extend(ull(x));
        }
        return pf.back();
    }
    ull query(int l, int r) const {
        assert(0 <= l && l <= r + 1 && r < n);
        return add(pf[r + 1], M - mul(pf[l], pw[r - l + 1]));
    }
};
const ull rolling_hash::B = hash61::B;
vector<ull> rolling_hash::pw = {1};

}  // namespace cplib

#endif  // CPLIB_ROLLING_HASH_HPP
