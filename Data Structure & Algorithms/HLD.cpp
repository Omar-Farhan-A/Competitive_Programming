struct HLD {
#define VAL_ON_EDGES 0
    const vector<vector<int>> &adj;
    vector<int> depth, par, root, pos, cntChildren, child;
    int cur_pos;

    HLD(int n, const vector<vector<int>> &G, int treeRoot = 1) : adj(G) {
        cur_pos = 1;
        depth = vector<int>(n + 5);
        par = vector<int>(n + 5);
        root = vector<int>(n + 5);
        pos = vector<int>(n + 5);
        cntChildren = vector<int>(n + 5);
        child = vector<int>(n + 5);
        init(treeRoot);
        build(treeRoot);
    }

    void init(int u, int p = -1, int d = 0) {
        depth[u] = d;
        par[u] = p;
        cntChildren[u] = 1;
        for (auto i: adj[u]) {
            if (i == p)continue;
            init(i, u, d + 1);
            cntChildren[u] += cntChildren[i];
            if (cntChildren[i] > cntChildren[child[u]]) {
                child[u] = i;
            }
        }
    }

    void build(int u, bool newChain = true) {
        root[u] = newChain ? u : root[par[u]];
        pos[u] = cur_pos++;
        if (child[u]) {
            build(child[u], false);
        }
        for (auto i: adj[u]) {
            if (i == par[u] || i == child[u])continue;
            build(i, true);
        }
    }

    pair<int, int> moveUp(int &u) {
        pair<int, int> ret = {pos[root[u]], pos[u]};
        u = par[root[u]];
        return ret;
    }

    void makeULower(int &u, int &v) {
        if (depth[root[u]] < depth[root[v]] || (root[u] == root[v] && depth[u] < depth[v])) {
            swap(u, v);
        }
    }

    vector<pair<int, int>> query(int u, int v) {
        vector<pair<int, int>> ret;
        while (root[u] != root[v]) {
            makeULower(u, v);
            ret.push_back(moveUp(u));
        }
        makeULower(u, v);
        if (!VAL_ON_EDGES)
            ret.push_back({pos[v], pos[u]});
        else if (u != v)
            ret.push_back({pos[v] + 1, pos[u]});
        return ret;
    }
};
