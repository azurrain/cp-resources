template<typename T>
T isqrt(T x, bool round_up = false) {
    assert(x >= 0);
    if (x == 0) return 0;
    T r = 2;
    bool dec = false;
    while (true) {
        T nr = (r + x / r) >> 1;
        if (r == nr || (r < nr && dec)) break;
        dec = (nr < r);
        r = nr;
    }
    if (round_up && r * r != x) ++r;
    return r;
}

template<typename T>
T bsgs(T a, T b, T p) {
    assert(a >= 0 && b >= 0 && p >= 1);
    if (a >= p) a %= p;
    if (b >= p) b %= p;
    if (a == 1) return (b == 1 ? 0 : -1);
    if (a == 0) return (b == 1 ? 0 : (b == 0 ? 1 : -1));
    T t = isqrt(p, true);
    T v = 1 % p;
    unordered_map<T, T> h;
    for (T i = 0; i < t; ++i) {
        h[b] = i;
        b = (ull)b * a % p;
        v = (ull)v * a % p;
    }
    a = 1 % p;
    for (T i = 0; i < t; ++i) {
        auto it = h.find(a);
        T j = (it == h.end() ? -1 : it->second);
        if (~j && i * t >= j) return i * t - j;
        a = (ull)a * v % p;
    }
    return -1;
}
