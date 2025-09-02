#ifndef CPLIB_CARTESIAN_TREE_HPP
#define CPLIB_CARTESIAN_TREE_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct cartesian_tree {
    int rt;
    vector<int> pa;
    vector<int> ls;
    vector<int> rs;
    cartesian_tree() : rt(-1), pa{}, ls{}, rs{} {
    }
    template<typename T, typename Cmp = less<T>>
    cartesian_tree(const vector<T> &a, const Cmp &cmp = {})
        : rt(-1), pa{}, ls{}, rs{} {
        int n = int(a.size());
        pa.resize(n, -1);
        ls.resize(n, -1);
        rs.resize(n, -1);
        stack<int> stk;
        for (int u = 0; u < n; ++u) {
            int last = -1;
            while (!stk.empty() && !cmp(a[u], a[stk.top()])) {
                last = stk.top();
                stk.pop();
            }
            if (!stk.empty()) {
                pa[u] = stk.top();
                rs[stk.top()] = u;
            } else {
                rt = u;
            }
            if (last != -1) {
                pa[last] = u;
                ls[u] = last;
            }
            stk.push(u);
        }
    }
};

}  // namespace cplib

#endif  // CPLIB_CARTESIAN_TREE_HPP
