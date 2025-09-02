#ifndef CPLIB_SCC_GRAPH_HPP
#define CPLIB_SCC_GRAPH_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct scc_graph {
    int n;
    vector<vector<int>> g;
    vector<vector<int>> groups;
    vector<int> ids;
    scc_graph() : scc_graph(0) {
    }
    explicit scc_graph(int n) : n(n), g(n), groups{}, ids{} {
    }
    void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        g[u].push_back(v);
    }
    void work() {
        groups.clear();
        ids.assign(n, 0);
        vector<int> ord;
        vector<vector<int>> gr(n);
        ord.reserve(n);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                gr[v].push_back(u);
            }
        }
        auto dfs1 = [&](auto &&self, int u) -> void {
            ids[u] = -1;
            for (int v : g[u]) {
                if (ids[v] == 0) {
                    self(self, v);
                }
            }
            ord.push_back(u);
        };
        auto dfs2 = [&](auto &&self, int u) -> void {
            groups.back().push_back(u);
            ids[u] = int(groups.size()) - 1;
            for (int v : gr[u]) {
                if (ids[v] == -1) {
                    self(self, v);
                }
            }
        };
        for (int u = 0; u < n; ++u) {
            if (ids[u] == 0) {
                dfs1(dfs1, u);
            }
        }
        for (int i = n - 1; i != -1; --i) {
            if (ids[ord[i]] == -1) {
                groups.emplace_back();
                dfs2(dfs2, ord[i]);
            }
        }
    }
};

}  // namespace cplib

#endif  // CPLIB_SCC_GRAPH_HPP
