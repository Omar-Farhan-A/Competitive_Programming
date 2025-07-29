struct DSU {
    vector<int> par, gp;
    stack<array<int, 5>> prev;
    int ans = 0;

    DSU(int n) {
        par.resize(n + 5);
        gp = vector<int>(n + 5, 1);
        std::iota(par.begin(), par.end(), 0);
        this->ans = n;
    }

    int getRoot(int u) {
        if (par[u] == u)return u;
        return getRoot(par[u]);
    }

    void merge(int u, int v) {
        v = getRoot(v), u = getRoot(u);
        if (u == v) {
            return;
        }
        if (gp[u] > gp[v])swap(u, v);

        prev.push({u, par[u], v, gp[v], ans});
        ans--;
        gp[v] += gp[u];
        par[u] = v;
    }

    void rollback() {
        auto s = prev.top();
        prev.pop();
        if (s[0] == -1) {
            return;
        }
        ans = s[4];
        par[s[0]] = s[1];
        gp[s[2]] = s[3];
    }

};
