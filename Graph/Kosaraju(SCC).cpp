vector<bool> vis;
void dfs(int v, vector<vector<int> > const &adj, vector<int> &output) {
    vis[v] = true;
    for (auto u: adj[v])
        if (!vis[u])
            dfs(u, adj, output);
    output.push_back(v);
}

void SCC(vector<vector<int> > const &adj,
         vector<vector<int> > &components,
         vector<vector<int> > &adj_cond) {
    int n = adj.size();
    components.clear(), adj_cond.clear();

    vector<int> order;
    vis.assign(n, false);
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i, adj, order);
    vector<vector<int> > adj_rev(n);
    for (int v = 0; v < n; v++)
        for (int u: adj[v])
            adj_rev[u].push_back(v);

    vis.assign(n, false);
    reverse(order.begin(), order.end());
    vector<int> roots(n, 0);
    for (auto v: order)
        if (!vis[v]) {
            std::vector<int> component;
            dfs(v, adj_rev, component);
            components.push_back(component);
            int root = *component.begin();
            for (auto u: component)
                roots[u] = root;
        }
    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u: adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}
