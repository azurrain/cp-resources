vector<double> gauss(vector<vector<double>> a, vector<double> b) {
    constexpr double eps = 1e-9;
    int n = a.size();
    if (n == 0) {
        return {};
    }
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(a[p][i]) < fabs(a[j][i])) {
                p = j;
            }
        }
        if (fabs(a[p][i]) < eps) {
            // No solution
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
