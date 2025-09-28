template<typename mint>
    requires (is_modint_v<mint>)
vector<mint> gauss(vector<vector<mint>> a, vector<mint> b) {
    int n = int(a.size());
    assert(n == int(a[0].size()));
    assert(n == int(b.size()));
    for (int i = 0; i < n; ++i) {
        int p = -1;
        for (int j = i; j < n; ++j) {
            if (a[j][i] != 0) {
                p = j;
                break;
            }
        }
        if (p == -1) {
            return {};
        }
        if (i != p) {
            swap(b[i], b[p]);
            swap(a[i], a[p]);
        }
        b[i] /= a[i][i];
        for (int k = n - 1; k >= i; --k) {
            a[i][k] /= a[i][i];
        }
        for (int j = i + 1; j < n; ++j) {
            b[j] -= b[i] * a[j][i];
            for (int k = n - 1; k >= i; --k) {
                a[j][k] -= a[i][k] * a[j][i];
            }
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int k = i + 1; k < n; ++k) {
            b[i] -= a[i][k] * b[k];
        }
    }
    return b;
}
