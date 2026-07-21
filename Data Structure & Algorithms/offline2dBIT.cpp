struct BIT2D {
    int n;
    vector<pair<int, int> > p;
    vector<int> st, ys;
    vector<ll> bit;

    void init(int N) {
        n = N;
        p.clear();
    }

    void prepare(int x, int y) {
        for (; x <= n; x += x & -x)
            p.push_back({x, y});
    }

    void build() {
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());

        st.assign(n + 2, 0);
        for (auto [x, y]: p) ++st[x + 1];
        for (int i = 1; i < st.size(); i++)
            st[i] += st[i - 1];
        ys.resize(p.size());
        for (int i = 0; i < p.size(); i++)
            ys[i] = p[i].second;

        bit.assign(p.size(), 0);
        p.clear();
    }

    void add(int x, int y, ll v) {
        for (; x <= n; x += x & -x) {
            int l = st[x], r = st[x + 1];
            int i = lower_bound(ys.begin() + l, ys.begin() + r, y) - ys.begin() - l + 1;
            for (; i <= r - l; i += i & -i)
                bit[l + i - 1] += v;
        }
    }

    ll sum(int x, int y) {
        ll res = 0;
        for (; x > 0; x -= x & -x) {
            int l = st[x], r = st[x + 1];
            int i = upper_bound(ys.begin() + l, ys.begin() + r, y) - ys.begin() - l;
            for (; i > 0; i -= i & -i)
                res += bit[l + i - 1];
        }
        return res;
    }

    ll sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};
