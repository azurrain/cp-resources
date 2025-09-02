ull mask = rng();

ull mapping(ull x) {
    x ^= mask;
    x ^= x << 16;
    x ^= x >> 13;
    x ^= x << 19;
    x ^= mask;
    return x;
}

vector<ull> get_hash(const vector<vector<int>> &g, int rt) {
    vector<ull> h(N, 1);
    auto dfs = [&](auto &&self, int u, int p) -> void {
        for (int v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            h[u] += mapping(h[v]);
        }
    };
    dfs(dfs, rt, -1);
    return h;
}
