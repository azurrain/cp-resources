#ifndef CPLIB_TWOSAT_HPP
#define CPLIB_TWOSAT_HPP 1

#include "cplib/scc_graph.hpp"

namespace cplib {

struct twosat {
    int n;
    scc_graph g;
    vector<bool> ans;
    twosat() : twosat(0) {
    }
    explicit twosat(int n) : n(n), g(2 * n), ans(n) {
    }
    void add(int x, bool vx) {
        assert(0 <= x && x < n);
        g.add(2 * x + !vx, 2 * x + vx);
    }
    void add(int x, bool vx, int y, bool vy) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        g.add(2 * x + !vx, 2 * y + vy);
        g.add(2 * y + !vy, 2 * x + vx);
    }
    bool solve() {
        g.work();
        const vector<int> &ids = g.ids;
        for (int u = 0; u < n; ++u) {
            if (ids[2 * u] == ids[2 * u + 1]) {
                return false;
            }
            ans[u] = ids[2 * u] < ids[2 * u + 1];
        }
        return true;
    }
};

}  // namespace cplib

#endif  // CPLIB_TWOSAT_HPP
