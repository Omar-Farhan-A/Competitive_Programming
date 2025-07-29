struct Edge {
    int u, v, w;
};
vector<Edge> adj;

ll Bellmanford(int src, int n) {
    vector<ll> dist(n + 5, 1e15);
    dist[src] = 0;
    bool ok = false;
    for (int i = 0; i < n; i++) {
        for (auto &[u, v, w]: adj) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (v == n && i == n - 1)ok = true;
            }
        }
    }
    if (ok)return -1e15;//negative cycle
    return dist[n];
}
