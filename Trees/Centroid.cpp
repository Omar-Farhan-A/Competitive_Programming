class Centroid {
private:
    vector<int> best, siz, par, vis, dep, rank;
    vector<vector<int>> adj, up;

    void dfs(int u = 1, int p = 0) {
        for (auto &v: adj[u]) {
            if (v == p)continue;
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < 20; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
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

    int find_size(int u, int p = -1) {
        if (vis[u])return 0;
        siz[u] = 1;
        for (auto &v: adj[u]) {
            if (v != p) {
                siz[u] += find_size(v, u);
            }
        }
        return siz[u];
    }

    int find_centroid(int u, int p, int n) {
        for (auto &v: adj[u]) {
            if (v != p) {
                if (!vis[v] && siz[v] > n / 2) {
                    return find_centroid(v, u, n);
                }
            }
        }
        return u;
    }

    void init_centroid(int u = 1, int p = -1) {
        find_size(u);
        int c = find_centroid(u, -1, siz[u]);
        vis[c] = 1;
        par[c] = p;
        rank[c] = (~p ? rank[p] + 1 : 0);
        for (auto &v: adj[c]) {
            if (!vis[v]) {
                init_centroid(v, c);
            }
        }
    }

    int dist(int u, int v) {
        int k = LCA(u, v);
        return dep[u] + dep[v] - (dep[k] << 1);
    }

public:
    void update(int u) {
        best[u] = 0;
        int v = u;
        while (~par[v]) {
            v = par[v];
            best[v] = min(best[v], dist(u, v));
        }
    }

    int query(int u) {
        int ans = best[u];
        int v = u;
        while (~par[v]) {
            v = par[v];
            ans = min(ans, best[v] + dist(u, v));
        }
        return ans;
    }

    Centroid(int n, vector<vector<int>> &adj) {
        vis = siz = par = dep = rank = vector<int>(n + 5);
        best = vector<int>(n + 5 ,2 * n);
        this->adj = adj;
        up = vector<vector<int>>(n + 5, vector<int>(20));
        dfs();
        init_centroid();
    }
};
