typedef pair<ll, ll> line;

struct node {
    line l;
    node *left, *right;

    node() : l({0, -1e18}), left(this), right(this) {}

    node(line l, node *L, node *R) : l(l), left(L), right(R) {}
};

node *const EMPTY = new node;

ll sub(const line &l, ll x) {
    return l.first * x + l.second;
}

double intersect(const line &l1, const line &l2) {
    assert(l1.first != l2.first);
    return (l2.second - l1.second) / (l1.first - l2.first - .0);
}

node *insert(node *cur, line l, int lx, int rx) {
    if (cur == EMPTY) {
        return new node(l, EMPTY, EMPTY);
    }
    node *res = new node(cur->l, cur->left, cur->right);
    // parallel
    if (l.first == res->l.first) {
        res->l = max(res->l, l);
        return res;
    }
    double x = intersect(l, res->l);
    if (x < lx || x > rx) {
        if (sub(l, lx) > sub(res->l, lx)) res->l = l;
        return res;
    }

    int m = lx + (rx - lx) / 2;

    if (x <= m) {
        if (sub(l, rx) > sub(res->l, rx)) swap(l, res->l);
        res->left = insert(res->left, l, lx, m);
    } else {
        if (sub(l, lx) > sub(res->l, lx)) swap(l, res->l);
        res->right = insert(res->right, l, m + 1, rx);
    }

    return res;
}

ll query(node *cur, int lx, int rx, ll x) {
    ll ret = sub(cur->l, x);
    if (lx == rx) return ret;

    int m = lx + (rx - lx) / 2;
    if (x <= m) return max(ret, query(cur->left, lx, m, x));
    return max(ret, query(cur->right, m + 1, rx, x));
}
