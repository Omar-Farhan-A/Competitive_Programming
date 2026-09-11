struct DSU {
    /*    Partially Persistent DSU
     *  hist[u] consists of {value,time}
     * if(value<0) then u is the root , size=-value
     * else par=value
    */
    vector<vector<pair<int, int> > > hist;

    int timer = 0;

    DSU(int n) {
        hist.resize(n + 1);
        for (int u = 0; u <= n; u++) {
            hist[u].push_back({-1, 0});
        }
    }

    int root(int u, int t) {
        auto [value, changeTime] = hist[u].back();
        if (value >= 0 && changeTime <= t)
            return root(value, t);
        return u;
    }

    bool merge(int u, int v) {
        ++timer;
        u = root(u, timer);
        v = root(v, timer);
        if (u == v)
            return false;
        int sizeU = -hist[u].back().first;
        int sizeV = -hist[v].back().first;
        if (sizeU < sizeV)
            swap(u, v);
        sizeU = -hist[u].back().first;
        sizeV = -hist[v].back().first;
        hist[u].push_back({-(sizeU + sizeV), timer});
        hist[v].push_back({u, timer});
        return true;
    }

    bool same(int u, int v, int t) {
        return root(u, t) == root(v, t);
    }

    int size(int u, int t) {
        u = root(u, t);
        int lo = 0;
        int hi = (int) hist[u].size() - 1;
        int ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (hist[u][mid].second <= t) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return -hist[u][ans].first;
    }
};
