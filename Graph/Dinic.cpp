template<typename T = ll>
struct FlowEdge {
    int u, v;
    T cap, flow = 0;

    FlowEdge(int u, int v, T cap) : u(u), v(v), cap(cap) {
    }
};

template<typename T = ll>
struct Dinic {
    const T flow_inf = numeric_limits<T>::max();
    vector<FlowEdge<T> > edges;
    vector<vector<int> > adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, T cap) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }

    bool full(int id) {
        return edges[id].cap == edges[id].flow;
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[t] = 0;
        q.push(t);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id: adj[u]) {
                int v = edges[id].v;
                if (level[v] != -1 || full(id ^ 1))
                    continue;
                level[v] = level[u] + 1;
                if (v == s)
                    return true;
                q.push(v);
            }
        }
        return false;
    }

    T dfs(int u, T pushed) {
        if (u == t)
            return pushed;
        T res = 0;
        for (int &cid = ptr[u]; cid < sz(adj[u]); cid++) {
            int id = adj[u][cid];
            int v = edges[id].v;
            if (level[v] != level[u] - 1 || full(id))
                continue;
            T tr = dfs(v, min(pushed - res, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            res += tr;
            if (res == pushed)
                return res;
        }
        level[u] = -1;
        return res;
    }

    T flow() {
        T f = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (T pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
