// root == n

vector<int> prufer(const vector<int> &pa) {
    int n = pa.size() + 1;
    if (n <= 2) return {};
    vector<int> deg(n, 1), c(n - 2);
    for (int u : pa) ++deg[u];
    for (int u = 0, i = 0; u < n - 1; ++u) {
        int v = u;
        while (i < n - 2 && deg[v] == 1 && v <= u) {
            --deg[v = pa[v]];
            c[i++] = v;
        }
    }
    return c;
}

vector<int> prufer_decode(const vector<int> &c) {
    int n = c.size() + 2;
    vector<int> deg(n, 1), pa(n - 1);
    for (int u : c) ++deg[u];
    for (int u = 0, i = 0; u < n - 1; ++u) {
        int v = u;
        while (deg[v] == 1 && v <= u) {
            pa[v] = i == n - 2 ? n - 1 : c[i++];
            --deg[v = pa[v]];
        }
    }
    return pa;
}
