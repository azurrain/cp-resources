namespace ac {

int ord(char c) { return c - 'a'; }  // 待定
const int N = 2000006, SIGMA = 26;   // 待定
int nxt[N][SIGMA], len[N], fail[N], tot = 1;

int new_node(int l = 0) {
    len[tot] = l;
    return tot++;
}

struct AC {
    int rt;
    AC() : rt(new_node()) {}
    int insert(const vector<int> &s) const {
        int u = rt;
        for (int k : s) {
            if (!nxt[u][k]) nxt[u][k] = new_node(len[u] + 1);
            u = nxt[u][k];
        }
        return u;
    }
    int insert(const string &s) const {
        vector<int> t(s.size());
        for (int i = 0; i < int(s.size()); ++i) t[i] = ord(s[i]);
        return insert(t);
    }
    void build() const {
        queue<int> q;
        for (int k = 0; k < SIGMA; ++k) {
            if (nxt[rt][k]) {
                fail[nxt[rt][k]] = rt;
                q.push(nxt[rt][k]);
            } else nxt[rt][k] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int k = 0; k < SIGMA; ++k) {
                if (nxt[u][k]) {
                    fail[nxt[u][k]] = nxt[fail[u]][k];
                    q.push(nxt[u][k]);
                } else nxt[u][k] = nxt[fail[u]][k];
            }
        }
    }
};

}  // namespace ac
using namespace ac;
