#ifndef CPLIB_BCCE_GRAPH_HPP
#define CPLIB_BCCE_GRAPH_HPP 1

#include "cplib/chminmax.hpp"

namespace cplib {

struct bcce_graph {
    int n;
    int m;
    vector<pair<int, int>> e;
    vector<vector<int>> g;
    vector<vector<int>> groups;
    vector<int> ids;
    vector<bool> bridge;
    bcce_graph() : bcce_graph(0) {
    }
    explicit bcce_graph(int n) : n(n), m(0), e{}, g(n), groups{}, ids{}, bridge{} {
    }
    void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        g[u].push_back(m);
        g[v].push_back(m);
        e.emplace_back(u, v);
        ++m;
    }
    void work() {
        groups.clear();
        ids.assign(n, -1);
        bridge.assign(m, false);
        vector<int> dep(n, -1);
        vector<int> low(n, -1);
        stack<int> stk;
        auto dfs = [&](auto &&self, int u, int pe) -> void {
            low[u] = dep[u];
            stk.push(u);
            for (int i : g[u]) {
                if (i == pe) {
                    continue;
                }
                int v = e[i].first ^ e[i].second ^ u;
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    self(self, v, i);
                    chmin(low[u], low[v]);
                } else {
                    chmin(low[u], dep[v]);
                }
            }
            if (dep[u] == low[u]) {
                groups.emplace_back();
                while (ids[u] == -1) {
                    int t = stk.top();
                    stk.pop();
                    groups.back().push_back(t);
                    ids[t] = int(groups.size()) - 1;
                }
                if (pe != -1) {
                    bridge[pe] = true;
                }
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

#endif  // CPLIB_BCCE_GRAPH_HPP
