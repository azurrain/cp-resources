// 求形如 x === a[i] (mod p[i]) 的方程组的最小非负整数解
ll crt(const vector<ll> &a, const vector<ll> &p) {
    int n = a.size();
    ll m = 1, r = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        m *= p[i];
    }
    for (int i = 0; i < n; ++i) {
        r = m / p[i];
        ans = (ans + a[i] * r * inv(r, p[i])) % m;
    }
    return ans;
}
