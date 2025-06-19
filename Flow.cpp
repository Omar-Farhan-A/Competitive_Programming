struct Edmonds_Karp {
    // O(V*E^2)
    int n;
    vector<vector<ll>> res;

    ll bfs(int s, int t, vector<int> &parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INF});
        while (!q.empty()) {
            int cur = q.front().first;
            ll flow = q.front().second;
            q.pop();
            for (int next = 0; next < n; next++) {
                if (parent[next] == -1 && res[cur][next]) {
                    parent[next] = cur;
                    ll new_flow = min(flow, res[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        vector<int> parent(n);
        int new_flow;
        while (new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                res[prev][cur] -= new_flow;
                res[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }

    Edmonds_Karp(vector<vector<pair<int, int>>> &adj) {
        n = adj.size();
        res = vector<vector<ll>>(n, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            for (auto &[v, w]: adj[i]) {
                res[i][v] += w;
            }
        }
    }
};

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;

    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    // O(V^2*E)
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id: adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int &cid = ptr[v]; cid < (int) adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};


struct HopcroftKarp {
    // O(sqrt(V)*E) 
    int n, m;
    vector<vector<int>> adj;
    vector<int> match, level;
    vector<bool> vis;

    HopcroftKarp(int n, int m) : n(n), m(m) {
        adj.resize(n);
        match.assign(n + m, -1);
        level.resize(n);
        vis.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v + n);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                level[i] = 0;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (match[v] == -1) {
                    return true;
                }
                if (level[match[v]] == -1) {
                    level[match[v]] = level[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return false;
    }

    bool dfs(int u) {
        vis[u] = true;
        for (int v: adj[u]) {
            if (match[v] == -1 || (!vis[match[v]] && level[match[v]] == level[u] + 1 && dfs(match[v]))) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int ans = 0;
        while (bfs()) {
            fill(vis.begin(), vis.end(), false);
            for (int i = 0; i < n; i++) {
                if (match[i] == -1 && dfs(i)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};


struct MCF
{
    const int INF = 1e9;
    struct Edge
    {
        int from, to, capacity, cost, flow;

        Edge(int from_, int to_, int capacity_, int cost_)
            : from(from_), to(to_), capacity(capacity_), cost(cost_), flow(0) {
        }
    };

    int n, s, t, k;
    vector<vector<int>> adj;
    vector<Edge> edges;
    vector<int> dist, parent;

    MCF(int n, int s, int t, int k) : n(n), s(s), t(t), k(k), dist(n), parent(n), adj(n) {}

    void add_edge(int u, int v, int cap, int cost) {
        edges.push_back({u, v, cap, cost});
        adj[u].push_back(sz(edges) - 1);
        edges.push_back({v, u, 0, -cost});
        adj[v].push_back(sz(edges) - 1);
    }

    bool dijkstra() {
        fill(dist.begin(), dist.end(), INF);
        fill(parent.begin(), parent.end(), -1);
        dist[s] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto d = pq.top().first;
            auto u = pq.top().second;
            pq.pop();
            if (d > dist[u]) continue;

            for (int idx : adj[u]) {
                Edge& e = edges[idx];
                if (e.flow < e.capacity && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent[e.to] = idx;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        return dist[t] != INF;
    }

    // just in case of negative edges
    bool bellman_ford() {
        fill(dist.begin(), dist.end(), INF);
        fill(parent.begin(), parent.end(), -1);
        dist[s] = 0;

        bool updated;
        for (int i = 0; i < n - 1; ++i) {
            updated = false;
            for (int u = 0; u < n; ++u) {
                if (dist[u] == INF) continue;
                for (int idx : adj[u]) {
                    Edge& e = edges[idx];
                    int v = e.to;
                    if (e.flow < e.capacity && dist[v] > dist[u] + e.cost) {
                        dist[v] = dist[u] + e.cost;
                        parent[v] = idx;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        return dist[t] != INF;
    }

    pair<int, int> minCostFlow() {
        int total_flow = 0, min_cost = 0;

        while (total_flow < k && dijkstra()) {
            int path_flow = k - total_flow;
            for (int v = t; v != s; v = edges[parent[v]].from) {
                path_flow = min(path_flow, edges[parent[v]].capacity - edges[parent[v]].flow);
            }

            for (int v = t; v != s; v = edges[parent[v]].from) {
                Edge& e = edges[parent[v]];
                e.flow += path_flow;
                edges[parent[v] ^ 1].flow -= path_flow;
                min_cost += path_flow * e.cost;
            }

            total_flow += path_flow;
        }

        return {total_flow, min_cost};
    }
};


struct HungarianAlgorithm {
    // if multiply instead of addition turn costs to their log and variables to double 
    int n;
    vector<vector<int>> cost;
    vector<int> u, v, p, way;
    const int INF = 1e9;

    HungarianAlgorithm(int n_, const vector<vector<int>>& cost_)
        : n(n_), cost(cost_), u(n_ + 1), v(n_ + 1), p(n_ + 1), way(n_ + 1) {
    }

    int solve(vector<int>& assignment) {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            vector<int> minv(n + 1, INF);
            vector<bool> used(n + 1, false);
            int j0 = 0;

            do {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1;

                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }

                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }
                    else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        // Create the assignment array from the resulting matching
        assignment.resize(n);
        for (int j = 1; j <= n; j++) {
            if (p[j] != 0) {
                assignment[p[j] - 1] = j - 1;  // worker (p[j] - 1) is assigned to task (j - 1)
            }
        }

        // Result: minimum cost
        return -v[0];
    }
};


struct Edge {
    int to;        // target node
    long double cost; // cost of sending flow through this edge
    int cap;       // capacity of the edge
    int flow;      // current flow through the edge
    int backEdge;  // index of the reverse edge in the adjacency list of 'to'
};

struct MCMF {
    const int inf = 1000000010;
    int n;
    vector<vector<Edge>> g;

    MCMF(int _n) {
        n = _n + 1;
        g.resize(n);
    }

    void addEdge(int u, int v, int cap, long double cost) {
        Edge e1 = {v, cost, cap, 0, (int) g[v].size()};
        Edge e2 = {u, -cost, 0, 0, (int) g[u].size()};
        g[u].push_back(e1);
        g[v].push_back(e2);
    }

    pair<long double, int> minCostMaxFlow(int s, int t) {
        int flow = 0;
        long double cost = 0;
        vector<int> state(n), from(n), from_edge(n);
        vector<long double> d(n);
        deque<int> q;
        while (true) {
            for (int i = 0; i < n; i++)
                state[i] = 2, d[i] = inf, from[i] = -1;
            state[s] = 1;
            q.clear();
            q.push_back(s);
            d[s] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop_front();
                state[v] = 0;
                for (int i = 0; i < (int) g[v].size(); i++) {
                    Edge &e = g[v][i];
                    if (e.flow >= e.cap || (d[e.to] <= d[v] + e.cost))
                        continue;
                    int to = e.to;
                    d[to] = d[v] + e.cost;
                    from[to] = v;
                    from_edge[to] = i;
                    if (state[to] == 1) continue;
                    if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
                        q.push_front(to);
                    else q.push_back(to);
                    state[to] = 1;
                }
            }
            if (d[t] == inf) break;
            int it = t, addflow = inf;
            while (it != s) {
                addflow = min(addflow,
                              g[from[it]][from_edge[it]].cap
                              - g[from[it]][from_edge[it]].flow);
                it = from[it];
            }
            it = t;
            while (it != s) {
                g[from[it]][from_edge[it]].flow += addflow;
                g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
                cost += g[from[it]][from_edge[it]].cost * addflow;
                it = from[it];
            }
            flow += addflow;
        }
        return {cost, flow};
    }
};
