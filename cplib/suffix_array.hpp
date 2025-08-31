#ifndef CPLIB_SUFFIX_ARRAY_HPP
#define CPLIB_SUFFIX_ARRAY_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

template<typename Cont>
vector<int> suffix_array(const Cont &s) {
    int n = int(s.size());
    if (n == 0) {
        return {};
    }
    vector<int> sa(n);
    vector<int> rk(n);
    vector<int> tmp = {};
    vector<int> cnt(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int x, int y) -> bool {
        return s[x] < s[y];
    });
    rk[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i - 1]] < s[sa[i]]);
    }
    tmp.reserve(n);
    int m = 1;
    while (rk[sa[n - 1]] < n - 1) {
        for (int i = 0; i < m; ++i) {
            tmp.push_back(n - m + i);
        }
        for (int i = 0; i < n; ++i) {
            if (sa[i] >= m) {
                tmp.push_back(sa[i] - m);
            }
        }
        for (int i = 0; i < n; ++i) {
            ++cnt[rk[i]];
        }
        for (int i = 1; i < n; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i != -1; --i) {
            sa[--cnt[rk[tmp[i]]]] = tmp[i];
        }
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int d = (rk[sa[i - 1]] < rk[sa[i]] ||
                     sa[i - 1] + m == n ||
                     rk[sa[i - 1] + m] < rk[sa[i] + m]);
            tmp[sa[i]] = tmp[sa[i - 1]] + d;
        }
        rk.swap(tmp);
        tmp.clear();
        fill(cnt.begin(), cnt.begin() + rk[sa[n - 1]] + 1, 0);
        m <<= 1;
    }
    return sa;
}

template<typename Cont>
vector<int> lcp_array(const Cont &s, const vector<int> &sa) {
    int n = int(s.size());
    if (n <= 1) {
        return {};
    }
    vector<int> rk(n);
    vector<int> lcp(n - 1);
    for (int i = 0; i < n; ++i) {
        rk[sa[i]] = i;
    }
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (h != 0) {
            --h;
        }
        if (rk[i] == n - 1) {
            continue;
        }
        int j = sa[rk[i] + 1];
        while (max(i, j) + h < n && s[i + h] == s[j + h]) {
            ++h;
        }
        lcp[rk[i]] = h;
    }
    return lcp;
}

}  // namespace cplib

#endif  // CPLIB_SUFFIX_ARRAY_HPP
