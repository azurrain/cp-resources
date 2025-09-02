#ifndef CPLIB_DIVIDING_TREE_HPP
#define CPLIB_DIVIDING_TREE_HPP 1

#include "cplib/bit.hpp"

namespace cplib {

template<typename T, typename Cmp = less<T>>
struct dividing_tree {
    int n;
    int m;
    int h;
    vector<vector<int>> ids;
    vector<vector<int>> tol;
    dividing_tree() : n(0), m(0), h(-1), ids{}, tol{} {
    }
    dividing_tree(const vector<T> &a, const Cmp &cmp = {})
        : n(int(a.size())), m(0), h(-1), ids{}, tol{} {
        if (n == 0) {
            return;
        }
        m = ceil2(n);
        h = ilog2(m);
        ids.resize(h + 1, vector<int>(m));
        tol.resize(h, vector<int>(m + 1));
        iota(ids[h].begin(), ids[h].end(), 0);
        sort(ids[h].begin(), ids[h].begin() + n, [&](int i, int j) {
            return cmp(a[i], a[j]);
        });
        for (int i = h - 1; i != -1; --i) {
            int len = m >> i;
            for (int j = 0; j < m; j += len) {
                int l = j;
                int r = j + (len >> 1);
                int k = j;
                while (l < j + (len >> 1) && r < j + len) {
                    if (ids[i + 1][l] < ids[i + 1][r]) {
                        ids[i][k] = ids[i + 1][l];
                        ++tol[i][k];
                        ++l;
                    } else {
                        ids[i][k] = ids[i + 1][r];
                        ++r;
                    }
                    ++k;
                }
                while (l < j + (len >> 1)) {
                    ids[i][k] = ids[i + 1][l];
                    ++tol[i][k];
                    ++l;
                    ++k;
                }
                while (r < j + len) {
                    ids[i][k] = ids[i + 1][r];
                    ++r;
                    ++k;
                }
            }
            for (int j = m - 1; j != -1; --j) {
                tol[i][j] += tol[i][j + 1];
            }
        }
    }
    int kth(int l, int r, int k) const {
        assert(0 <= l && l < n);
        assert(0 <= r && r < n);
        assert(0 <= k && k < r - l + 1);
        int i = 0;
        int b = 0;
        int e = m;
        while (l < r) {
            int x = tol[i][b] - tol[i][l];
            int y = tol[i][l] - tol[i][r + 1];
            int rx = l - b - x;
            int ry = r - l + 1 - y;
            if (k < y) {
                e = (b + e) >> 1;
                l = b + x;
                r = l + y - 1;
            } else {
                b = (b + e) >> 1;
                l = b + rx;
                r = l + ry - 1;
                k -= y;
            }
            ++i;
        }
        return ids[i][l];
    }
};

}  // namespace cplib

#endif  // CPLIB_DIVIDING_TREE_HPP
