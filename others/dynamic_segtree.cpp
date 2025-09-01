using pos_t = int /* int or ll */;

struct info {
    // 成员变量
    friend info operator+(const info &a, const info &b) {
        info c = {};
        // 将左右子树信息 a, b 合并到 c
        return c;
    }
};

struct node {
    node *l = 0;
    node *r = 0;
    info s = {};
    void pull() {
        s = (l != 0 ? l->s : info{}) + (r != 0 ? r->s : info{});
    }
};

node *new_node() {
    static node pool[800005 /* 指定内存池大小 */] = {};
    static node *p = pool;
    return p++;

    // 不确定内存池大小可以用 deque
    // static deque<node> pool;
    // return &pool.emplace_back();
};

void modify(node *&u, pos_t l, pos_t r, pos_t p, const info &s) {
    if (u == 0) {
        u = new_node();
    }
    if (l == r) {
        u->s = s;
        return;
    }
    pos_t m = (l + r) >> 1;
    if (p <= m) {
        modify(u->l, l, m, p, s);
    } else {
        modify(u->r, m + 1, r, p, s);
    }
    u->pull();
}

node *insert(node *u, pos_t l, pos_t r, pos_t p, const info &s) {
    node *v = new_node();
    if (l == r) {
        v->s = s;
        return v;
    }
    if (u != 0) {
        v->l = u->l;
        v->r = u->r;
    }
    pos_t m = (l + r) >> 1;
    if (p <= m) {
        v->l = insert(v->l, l, m, p, s);
    } else {
        v->r = insert(v->r, m + 1, r, p, s);
    }
    v->pull();
    return v;
}

info query(node *u, pos_t l, pos_t r, pos_t ql, pos_t qr) {
    if (u == 0 || r < ql || qr < l) {
        return {};
    }
    if (ql <= l && r <= qr) {
        return u->s;
    }
    pos_t m = (l + r) >> 1;
    return query(u->l, l, m, ql, qr) + query(u->r, m + 1, r, ql, qr);
}

template<typename F> requires (is_convertible_v<F, function<bool(info)>>)
pos_t minr_impl(node *&u, pos_t l, pos_t r, info &cur, pos_t ql, F f) {
    if (r < ql) {
        return r + 1;
    }
    if (u == 0) {
        u = new_node();
    }
    if (ql <= l) {
        if (!f(cur + u->s)) {
            cur = cur + u->s;
            return r + 1;
        }
        if (l == r) {
            return r;
        }
    }
    pos_t m = (l + r) >> 1;
    pos_t qr = minr_impl(u->l, l, m, cur, ql, f);
    if (qr == m + 1) {
        qr = minr_impl(u->r, m + 1, r, cur, ql, f);
    }
    return qr;
}

template<typename F> requires (is_convertible_v<F, function<bool(info)>>)
pos_t minr(node *&u, pos_t l, pos_t r, pos_t ql, F f) {
    static info s = {};
    s = info{};
    return minr_impl(u, l, r, s, ql, f);
}
