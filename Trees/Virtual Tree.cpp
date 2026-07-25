const int N = 2e5 + 5;
vector<int> adj[N], adj_vt[N];
int up[N][20], in[N], out[N], dep[N], timer;
 
void dfs0(int u, int p) {
    in[u] = ++timer;
    for (int i = 1; i < 20; i++)up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v: adj[u]) {
        if (v == p)continue;
        up[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs0(v, u);
    }
    out[u] = timer;
}
 
bool isAnc(int u, int v) {
    // u is an ancestor of v
    return in[u] <= in[v] && out[v] <= out[u];
}
 
int lca(int u, int v) {
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    for (int i = 19; i >= 0; i--) {
        if (dep[u] < (1 << i))continue;
        if (!isAnc(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}
 
struct virtual_tree {
    vector<int> used;
 
    vector<int> build(vector<int> v) {
        if (v.empty())return {};
 
        sort(v.begin(), v.end(), [&](int x, int y) {
            return in[x] < in[y];
        });
        int k = sz(v);
        for (int i = 0; i < k - 1; i++) {
            v.push_back(lca(v[i], v[i + 1]));
        }
        sort(v.begin(), v.end(), [&](int x, int y) {
            return in[x] < in[y];
        });
        v.erase(unique(v.begin(), v.end()), v.end());
        stack<int> st;
        st.push(v[0]);
        for (int i = 1; i < sz(v); i++) {
            while (!isAnc(st.top(), v[i])) {
                st.pop();
            }
            adj_vt[st.top()].push_back(v[i]), used.push_back(st.top());
            st.push(v[i]);
        }
        return v;
      // v[0] is the root
    }
 
    void clear() {
        for (int u: used)adj_vt[u].clear();
        used.clear();
    }
};
