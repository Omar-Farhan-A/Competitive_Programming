class Binary_lifting {
private:
    vector<vector<int>> adj, up;
    int timer;
    void dfs(int u = 1, int p = 0) {
        in[u]=++timer;
        for (auto &v: adj[u]) {
            if (v == p)continue;
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < 20; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
        out[u]=++timer;
    }

public:
    vector<int> dep, in, out;

    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    int LCA(int u, int v) {
        if (dep[u] < dep[v])swap(u, v);
        int k = dep[u] - dep[v];
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 19; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int Kth_anc(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }
        return u;
    }

    int dist(int u, int v) {
        int k = LCA(u, v);
        return dep[u] + dep[v] - (dep[k] << 1);
    }

    Binary_lifting(int n, vector<vector<int>> &adj...) {
        in=out=dep=vector<int>(n+5);
        this->adj = adj;
        up.resize(n + 5, vector<int>(20));
        timer=0;
        dfs();
    }
};
