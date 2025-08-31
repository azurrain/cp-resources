#ifndef CPLIB_HLD_HPP
#define CPLIB_HLD_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct hld {
    int n;
    vector<vector<int>> g;
    vector<int> par;
    vector<int> dep;
    vector<int> siz;
    vector<int> lnk;
    vector<int> dfn;
    vector<int> ord;
    vector<int> top;
    hld() : hld(0) {
    }
    explicit hld(int n) : n(n), g(n), par{}, dep{}, siz{}, lnk{}, dfn{}, ord{}, top{} {
    }
    void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void work(int rt) {
        assert(0 <= rt && rt < n);
        par.assign(n, -1);
        dep.assign(n, 0);
        siz.assign(n, 1);
        lnk.assign(n, -1);
        dfn.assign(n, -1);
        ord.clear();
        ord.reserve(n);
        top.assign(n, -1);
        auto dfs1 = [&](auto &&self, int u) -> void {
            for (int v : g[u]) {
                if (v == par[u]) {
                    continue;
                }
                par[v] = u;
                dep[v] = dep[u] + 1;
                self(self, v);
                siz[u] += siz[v];
                if (lnk[u] == -1 || siz[lnk[u]] < siz[v]) {
                    lnk[u] = v;
                }
            }
        };
        auto dfs2 = [&](auto &&self, int u, int t) -> void {
            dfn[u] = int(ord.size());
            ord.push_back(u);
            top[u] = t;
            if (lnk[u] != -1) {
                self(self, lnk[u], t);
            }
            for (int v : g[u]) {
                if (v != par[u] && v != lnk[u]) {
                    self(self, v, v);
                }
            }
        };
        dfs1(dfs1, rt);
        dfs2(dfs2, rt, rt);
    }
    template<typename T>
    void dfn_sort(vector<T> &a) const {
        assert(int(a.size()) == n);
        vector<T> t(n);
        for (int i = 0; i < n; ++i) {
            t[dfn[i]] = a[i];
        }
        a.swap(t);
    }
    int lca(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = par[top[u]];
        }
        return (dep[u] < dep[v] ? u : v);
    }
    template<typename F> requires (is_convertible_v<F, function<void(int, int)>>)
    void apply(int u, int v, const F &f, bool includes_lca = true) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            f(dfn[top[u]], dfn[u]);
            u = par[top[u]];
        }
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        if (includes_lca) {
            f(dfn[u], dfn[v]);
        } else if (u != v) {
            f(dfn[u] + 1, dfn[v]);
        }
    }
};

}  // namespace cplib

#endif  // CPLIB_HLD_HPP
