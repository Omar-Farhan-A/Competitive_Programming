vector<int> is_query(N);
 
struct DC {
    vector<vector<pair<int, int> > > edges;
    int siz;
 
    DC(int n) {
        siz = 1;
        while (siz < n) siz <<= 1;
        edges.resize(siz << 1);
    }
 
    void add_edge(int x, int lx, int rx, int l, int r, int u, int v) {
        if (lx > r || rx < l)return;
        if (l <= lx && rx <= r) {
            edges[x].push_back({u, v});
            return;
        }
        int m = (lx + rx) >> 1;
        add_edge(2 * x + 1, lx, m, l, r, u, v);
        add_edge(2 * x + 2, m + 1, rx, l, r, u, v);
    }
 
    void dfs(int x, int lx, int rx, RollbackDSU &ds) {
        int snapshot = ds.snapshot();
        for (auto [u,v]: edges[x])ds.merge(u, v);
        if (lx == rx) {
            if (lx < sz(is_query) && is_query[lx]) {
                cout << ds.components << " ";
            }
        } else {
            int m = (lx + rx) >> 1;
            dfs(2 * x + 1, lx, m, ds);
            dfs(2 * x + 2, m + 1, rx, ds);
        }
        ds.rollback(snapshot);
    }
 
    void add_edge(int u, int v, int l, int r) {
        add_edge(0, 0, siz - 1, l, r, u, v);
    }
 
    void dfs(RollbackDSU &ds) {
        dfs(0, 0, siz - 1, ds);
    }
};
