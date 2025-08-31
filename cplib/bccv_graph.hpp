#ifndef CPLIB_BCCV_GRAPH_HPP
#define CPLIB_BCCV_GRAPH_HPP 1

#include "cplib/chminmax.hpp"

namespace cplib {

struct bccv_graph {
    int n;
    vector<vector<int>> g;
    vector<vector<int>> groups;
    vector<bool> cut;
    bccv_graph() : bccv_graph(0) {
    }
    explicit bccv_graph(int n) : n(n), g(n), groups{}, cut(n) {
    }
    void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void work() {
        groups.clear();
        cut.assign(n, false);
        vector<int> dep(n, -1);
        vector<int> low(n, -1);
        stack<int> stk;
        auto dfs = [&](auto &&self, int u, int pv) -> void {
            low[u] = dep[u];
            stk.push(u);
            bool leq = false;
            for (int v : g[u]) {
                if (dep[v] != -1) {
                    chmin(low[u], dep[v]);
                    continue;
                }
                dep[v] = dep[u] + 1;
                self(self, v, u);
                chmin(low[u], low[v]);
                if (dep[u] <= low[v]) {
                    groups.push_back({u});
                    int t = -1;
                    do {
                        t = stk.top();
                        stk.pop();
                        groups.back().push_back(t);
                    } while (t != v);
                    cut[u] = (pv != -1 || leq);
                    leq = true;
                }
            }
            if (pv == -1 && !leq) {
                groups.push_back({u});
            }
        };
        for (int u = 0; u < n; ++u) {
            if (dep[u] == -1) {
                dep[u] = 0;
                dfs(dfs, u, -1);
            }
        }
    }
};

}  // namespace cplib

#endif  // CPLIB_BCCV_GRAPH_HPP
