namespace pam {

int ord(char c) { return c - 'a'; }  // 待定
const int N = 1000006, SIGMA = 26;   // 待定
int nxt[N][SIGMA], len[N], fail[N], tot = 1;

int new_node(int l = 0, int f = 0) {
    len[tot] = l;
    fail[tot] = f;
    return tot++;
}

struct PAM {
    string s;
    int rt[2], last;
    PAM() : s{}, rt{}, last(tot + 1) { rt[1] = new_node(-1, tot), rt[0] = new_node(0, tot - 1); }
    int extend(char c) {
        s.push_back(c);
        int u = getfail(last), k = ord(c);
        if (!nxt[u][k]) {
            int v = new_node(len[u] + 2, max(rt[0], nxt[getfail(fail[u])][k]));
            nxt[u][k] = v;
        }
        return last = nxt[u][k];
    }
    int getfail(int u) const {
        while (len[u] + 1U == s.size() || s.end()[-len[u] - 2] != s.back()) u = fail[u];
        return u;
    }
};

}  // namespace pam
using namespace pam;
