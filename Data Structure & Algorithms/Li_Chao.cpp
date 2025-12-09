typedef pair<ll, ll> line;
extern struct node *const EMPTY;

ll sub(const line &l, ll x) {
    return l.first * x + l.second;
}

double intersect(const line &l1, const line &l2) {
    assert(l1.first != l2.first);
    return (l2.second - l1.second) / (l1.first - l2.first - .0);

}

struct node {
    line l;
    node *left, *right;

    node() : l({0, -1e18}), left(this), right(this) {}

    node(line l) : l(l), left(EMPTY), right(EMPTY) {}
};

node *const EMPTY = new node;

void insert(node *&cur, line l, int lx, int rx) {
    if (cur == EMPTY) {
        cur = new node(l);
        return;
    }
    // parallel
    if (l.first == cur->l.first) {
        cur->l = max(cur->l, l);
        return;
    }
    auto x = intersect(l, cur->l);
    if (x < lx || x > rx) {
        if (sub(l, lx) > sub(cur->l, lx))cur->l = l;
        return;
    }
    int m = lx + (rx - lx) / 2;
    if (x <= m) {
        if (sub(l, rx) > sub(cur->l, rx))swap(l, cur->l);
        insert(cur->left, l, lx, m);
    } else {
        if (sub(l, lx) > sub(cur->l, lx))swap(l, cur->l);
        insert(cur->right, l, m + 1, rx);
    }

}

ll query(node *cur, int lx, int rx, ll x) {
    if (x < lx || x > rx)return LONG_LONG_MAX;
    ll ret = sub(cur->l, x);
    if (lx == rx)return ret;
    int m = lx + (rx - lx) / 2;
    if (x <= m) {
        return max(ret, query(cur->left, lx, m, x));
    }
    return max(ret, query(cur->right, m + 1, rx, x));
}

//  node *root = EMPTY;
//for min -> insert({-m,-c}}),ans=-query() 
