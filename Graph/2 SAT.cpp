struct TwoSat {
    int n;
    vector<vector<int> > g, rg;
    vector<int> vis, comp, ord, ans;

    TwoSat(int n) : n(n) {
        g.resize(2 * n);
        rg.resize(2 * n);
        comp.resize(2 * n, -1);
        vis.resize(2 * n);
        ans.resize(n);
    }

    int node(int x, bool v) {
        return 2 * x + v;
    }

    int neg(int x) {
        return x ^ 1;
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    // (a OR b)
    void add_or(int x, bool xv, int y, bool yv) {
        int a = node(x, xv);
        int b = node(y, yv);
        add_edge(neg(a), b);
        add_edge(neg(b), a);
    }

    // (a != b)
    void add_xor(int a, int b) {
        //(a or b) and (!a or !b)
        add_or(a, true, b, true);
        add_or(a, false, b, false);
    }

    // (a = b)
    void add_equal(int a, int b) {
        // (a or !b) and  (!a or b)
        add_or(a, true, b, false);
        add_or(a, false, b, true);
    }

    // x = val
    void set(int x, bool val) {
        add_or(x, val, x, val);
    }

    // (a AND b) must be true
    void add_and(int a, int b) {
        set(a, true);
        set(b, true);
    }

    // !(a AND b) = (!a OR !b)
    void add_nand(int a, int b) {
        add_or(a, false, b, false);
    }

    // !(a OR b) = (!a AND !b)
    void add_nor(int a, int b) {
        set(a, false);
        set(b, false);
    }

    // (a XNOR b) = (a == b)
    void add_xnor(int a, int b) {
        add_equal(a, b);
    }

    // (a -> b) = (!a OR b)
    void add_implies(int a, int b) {
        add_or(a, false, b, true);
    }

    // At most one of a, b is true
    void at_most_one(int a, int b) {
        add_or(a, false, b, false);
    }

    // At least one of a, b is true
    void at_least_one(int a, int b) {
        add_or(a, true, b, true);
    }

    // Exactly one of a, b is true
    void exactly_one(int a, int b) {
        add_xor(a, b);
    }

    // Forbid (a == av AND b == bv)
    void forbid(int a, bool av, int b, bool bv) {
        add_or(a, !av, b, !bv);
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v])dfs1(v);
        }
        ord.push_back(u);
    }

    void dfs2(int u, int id) {
        comp[u] = id;
        for (int v: rg[u]) {
            if (comp[v] == -1)dfs2(v, id);
        }
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i++) {
            if (!vis[i])dfs1(i);
        }
        reverse(ord.begin(), ord.end());
        int cnt = 0;
        for (int u: ord) {
            if (comp[u] == -1)dfs2(u, cnt++);
        }
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1])return false;
        }
        for (int i = 0; i < n; i++) {
            ans[i] = comp[2 * i + 1] > comp[2 * i];
        }
        return true;
    }
};
