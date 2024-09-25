int fre[N];
template<typename T = int>
class MO_on_tree {
public:
    vector<vector<int>> adj, up;
    vector<int> dep;
    int SQ, q;
    T ans;
    struct Query {
        int l, r, idx, lc;
    };
    vector<Query> Q;
    vector<T> a;
    vector<int> vis, in, out, id;
    int timer;

    void dfs(int u, int p) {
        in[u] = ++timer;
        id[timer] = u;
        for (auto &v: adj[u]) {
            if (p == v)continue;
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < 20; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
        out[u] = ++timer;
        id[timer] = u;
    }

    void check(int u) {
        // If (u) occurs twice, then don't consider its value
        if (vis[u] && (--fre[a[u]] == 0))--ans;
        else if (!vis[u] && !fre[a[u]]++)++ans;
        vis[u] ^= 1;
    }

    T calc(...) {
        return ans;
    }

    MO_on_tree(vector<T> &a, vector<vector<int>> &adj) {
        q = 0;
        ans = 0;
        timer = 0;
        this->a = a;
        this->adj = adj;
        int n = a.size();
        in = out = dep = vis = vector<int>(n + 5);
        SQ = sqrt(n << 1);
        id.resize(2 * n + 5);
        up = vector<vector<int>>(n + 5, vector<int>(20));
        dfs(1, 0);
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

    void add_query(int l, int r, int lc) {
        Q.push_back({l, r, q++, lc});
    }

    void process() {
        vector<T> ans_query(q);
        std::sort(Q.begin(), Q.end(), [&](Query &x, Query &y) {
            if (x.l / SQ != y.l / SQ) {
                return x.l / SQ < y.l / SQ;
            }
            return x.r < y.r;
        });
        int curL = 1, curR = 0;
        for (int i = 0; i < Q.size(); i++) {
            int L = Q[i].l, R = Q[i].r, lc = Q[i].lc, idx = Q[i].idx;
            while (curL < L) check(id[curL++]);
            while (curL > L) check(id[--curL]);
            while (curR < R) check(id[++curR]);
            while (curR > R) check(id[curR--]);
            int u = id[curL], v = id[curR];
            if (lc != u and lc != v) check(lc);
            ans_query[idx] = calc();
            if (lc != u and lc != v) check(lc);
        }
        for (auto it: ans_query) {
            cout << it << '\n';
        }
        for (int i = curL; i <= curR; i++)check(id[i]);
    }
};

void burn() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (!m[x])m[x] = i;
        a[i] = m[x];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    MO_on_tree<int> mo(a, adj);
    for (int i = 0; i < q; i++) {
        int u, v, lc;
        cin >> u >> v;
        lc = mo.LCA(u, v);
        if (mo.in[u] > mo.in[v])swap(u, v);
        int l, r;
        if (lc == u) l = mo.in[u], r = mo.in[v];
        else l = mo.out[u], r = mo.in[v];
        mo.add_query(l, r, lc);
    }
    mo.process();
}
