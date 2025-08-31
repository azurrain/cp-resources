#ifndef CPLIB_MCF_GRAPH_HPP
#define CPLIB_MCF_GRAPH_HPP 1

#include "cplib/chminmax.hpp"

namespace cplib {

template<typename Cap, typename Cost> requires (is_signed_v<Cost>)
struct mcf_graph {
    struct sedge {
        int to;
        Cap cap;
        Cost cost;
        sedge() : sedge(-1, 0, 0) {
        }
        sedge(int v, Cap c, Cost w) : to(v), cap(c), cost(w) {
        }
    };
    struct edge {
        int from;
        int to;
        Cap cap;
        Cap flow;
        Cost cost;
        edge() : edge(-1, -1, 0, 0, 0) {
        }
        edge(int u, int v, Cap c, Cap f, Cost w)
            : from(u), to(v), cap(c), flow(f), cost(w) {
        }
    };
    int n;
    int m;
    vector<sedge> e;
    vector<vector<int>> g;
    mcf_graph() : mcf_graph(0) {
    }
    explicit mcf_graph(int n) : n(n), m(0), e{}, g(n) {
    }
    void add(int u, int v, Cap c, Cost w) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(0 <= c);
        assert(0 <= w);
        e.emplace_back(v, c, w);
        e.emplace_back(u, 0, -w);
        g[u].push_back(2 * m);
        g[v].push_back(2 * m + 1);
        ++m;
    }
    void set_edge(int i, Cap c, Cap f, Cost w) {
        assert(0 <= i && i < m);
        assert(0 <= f && f <= c);
        assert(0 <= w);
        e[2 * i].cap = c - f;
        e[2 * i].cost = w;
        e[2 * i + 1].cap = f;
        e[2 * i + 1].cost = -w;
    }
    edge get_edge(int i) const {
        assert(0 <= i && i < m);
        return edge(e[2 * i + 1].to, e[2 * i].to,
                    e[2 * i].cap + e[2 * i + 1].cap, e[2 * i + 1].cap,
                    e[2 * i].cost);
    }
    vector<edge> edges() const {
        vector<edge> t;
        t.reserve(m);
        for (int i = 0; i < m; ++i) {
            t.push_back(get_edge(i));
        }
        return t;
    }
    pair<Cap, Cost> flow(int s, int t, Cap lim = numeric_limits<Cap>::max()) {
        assert(0 <= s && s < n);
        assert(0 <= t && t < n);
        assert(s != t);
        return slope(s, t, lim).back();
    }
    vector<pair<Cap, Cost>> slope(int s, int t, Cap lim = numeric_limits<Cap>::max()) {
        assert(0 <= s && s < n);
        assert(0 <= t && t < n);
        assert(s != t);
        static constexpr Cost INF = numeric_limits<Cost>::max();
        vector<Cost> d(n);
        vector<Cost> h(n);
        vector<int> pe(n);
        auto dijkstra = [&]() -> bool {
            fill(d.begin(), d.end(), INF);
            fill(pe.begin(), pe.end(), -1);
            d[s] = 0;
            priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<>> q;
            q.emplace(0, s);
            while (!q.empty()) {
                auto [du, u] = q.top();
                q.pop();
                if (du != d[u]) {
                    continue;
                }
                for (int i : g[u]) {
                    auto [v, c, w] = e[i];
                    if (c > 0 && d[v] > du + w + h[u] - h[v]) {
                        d[v] = du + w + h[u] - h[v];
                        pe[v] = i;
                        q.emplace(d[v], v);
                    }
                }
            }
            return d[t] != INF;
        };
        vector<pair<Cap, Cost>> res;
        Cap flow = 0;
        Cost cost = 0;
        Cost last = -1;
        while (flow < lim && dijkstra()) {
            for (int i = 0; i < n; ++i) {
                if (d[i] != INF) {
                    h[i] += d[i];
                }
            }
            Cap f = lim - flow;
            for (int u = t; u != s; u = e[pe[u] ^ 1].to) {
                chmin(f, e[pe[u]].cap);
            }
            for (int u = t; u != s; u = e[pe[u] ^ 1].to) {
                e[pe[u]].cap -= f;
                e[pe[u] ^ 1].cap += f;
            }
            if (last != h[t]) {
                last = h[t];
                res.emplace_back(flow, cost);
            }
            flow += f;
            cost += f * h[t];
        }
        res.emplace_back(flow, cost);
        return res;
    }
};

}  // namespace cplib

#endif  // CPLIB_MCF_GRAPH_HPP
