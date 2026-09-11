struct RollbackDSU {
    vector<int> par, sz;
    stack<array<int, 4> > history;
    int components;

    RollbackDSU(int n) {
        par.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(par.begin(), par.end(), 0);
        components = n;
    }

    int find(int u) {
        if (par[u] == u)
            return u;
        return find(par[u]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        if (sz[u] > sz[v])
            swap(u, v);
        history.push({u, v, sz[v], components});
        par[u] = v;
        sz[v] += sz[u];
        components--;
        return true;
    }

    int snapshot() {
        return history.size();
    }

    void rollback() {
        auto [u, v, oldSizeV, oldComponents] = history.top();
        history.pop();
        par[u] = u;
        sz[v] = oldSizeV;
        components = oldComponents;
    }

    void rollback(int snap) {
        while ((int) history.size() > snap)
            rollback();
    }
};
