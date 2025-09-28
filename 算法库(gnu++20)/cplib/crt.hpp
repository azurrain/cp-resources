#ifndef CPLIB_CRT_HPP
#define CPLIB_CRT_HPP 1

#include "cplib/safe_mod.hpp"
#include "cplib/inv.hpp"

namespace cplib {

template<integral T>
pair<ll, ll> crt(const vector<T> &r, const vector<T> &m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    ll r0 = 0;
    ll m0 = 1;
    for (int i = 0; i < n; ++i) {
        assert(m[i] >= 1);
        ll r1 = safe_mod(ll(r[i]), ll(m[i]));
        ll m1 = ll(m[i]);
        if (m0 < m1) {
            swap(m0, m1);
            swap(r0, r1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) {
                return {0LL, 0LL};
            }
            continue;
        }
        auto [im, g] = inv_gcd(m0, m1);
        if ((r1 - r0) % g != 0) {
            return {0LL, 0LL};
        }
        ll u1 = m1 / g;
        r0 += (r1 - r0) / g % u1 * im % u1 * m0;
        m0 *= u1;
        if (r0 < 0) {
            r0 += m0;
        }
    }
    return {r0, m0};
}

}  // namespace cplib

#endif  // CPLIB_CRT_HPP
