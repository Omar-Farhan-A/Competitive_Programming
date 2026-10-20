const int N = 2e5 + 5,NODES=4e6 + 5;
int id = 1;
int pl[NODES], pr[NODES];
ll sum[NODES];
int root[N];
// Point update: add v to position i
int update(int p, int l, int r, int i, ll v) {
    if (!p) p = id++;
    if (l == r) {
        sum[p] += v;
        return p;
    }
    int m = (l + r) / 2;
    if (i <= m)
        pl[p] = update(pl[p], l, m, i, v);
    else
        pr[p] = update(pr[p], m + 1, r, i, v);
    sum[p] = sum[pl[p]] + sum[pr[p]];
    return p;
}

// Range sum query [i, j]
ll query(int p, int l, int r, int i, int j) {
    if (!p || i > r || j < l) return 0;
    if (i <= l && r <= j)
        return sum[p];
    int m = (l + r) / 2;
    return query(pl[p], l, m, i, j) + query(pr[p], m + 1, r, i, j);
}

// Merge p2 into p1 (destructive)
int merge(int p1, int p2, int l, int r) {
    if (!p1) return p2;
    if (!p2) return p1;
    if (l == r) {
        sum[p1] += sum[p2];
        return p1;
    }
    int m = (l + r) / 2;
    pl[p1] = merge(pl[p1], pl[p2], l, m);
    pr[p1] = merge(pr[p1], pr[p2], m + 1, r);
    sum[p1] = sum[pl[p1]] + sum[pr[p1]];
    return p1;
}

void solve() {
    int n, q;
    cin >> n >> q;
    // Each root[k] represents a separate segment tree.
    // All trees cover the domain [1, n].
    // Type 1: 1 k pos val
    //   Add val at pos in tree k.
    // Type 2: 2 a b
    //   Merge tree b into tree a.
    //   Tree b becomes empty.
    // Type 3: 3 k l r
    //   Query sum [l, r] in tree k.
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, pos;
            ll val;
            cin >> k >> pos >> val;
            root[k] = update(root[k], 1, n, pos, val);
        } else if (type == 2) {
            int a, b;
            cin >> a >> b;
            if (a == b) continue;
            root[a] = merge(root[a], root[b], 1, n);
            root[b] = 0;
        } else if (type == 3) {
            int k, l, r;
            cin >> k >> l >> r;
            cout << query(root[k], 1, n, l, r) << '\n';
        }
    }
}
