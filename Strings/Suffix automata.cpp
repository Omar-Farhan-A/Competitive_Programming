/*
 *  st[u] ---> one equivalence class of substrings having the same endpos set
 *  st[u].len---> maximum length of a substring represented by state u
 *  st[st[u].link].len+1 minimum length of a substring represented by state u
 *  cnt[u]---> number of occurrences for all substrings represented by state u
 *  dp[u]---> number of paths/substrings starting at state u including empty path
 *  dp_dis[u]---> number distinct paths/substrings starting at state u including empty path
    SMALLEST CYCLIC SHIFT ->  build SAM for: S + S then greedily take minimum
    lexicographical transition until path length = |S|.
 */
struct SAM {
    struct State {
        int len = 0, link = 0;
        map<char, int> nxt;
    };

    vector<State> st;
    vector<int> cnt, idx;
    vector<ll> dp, dp_dis;
    int last = 0, sz = 0;

    SAM(int n) {
        st.assign(2 * n, {});
        st[0].link = -1;
        cnt.resize(2 * n);
        idx.assign(2 * n, n);
        dp_dis.assign(2 * n, -1);
        dp.assign(2 * n, -1);
    }

    void insert(char c) {
        int cur = ++sz;
        st[cur].len = st[last].len + 1;
        cnt[cur] = 1;
        idx[cur] = st[cur].len - 1;
        int p = last;
        while (~p && st[p].nxt.count(c) == 0) {
            st[p].nxt[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].nxt[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int clone = ++sz;
                st[clone].len = st[p].len + 1;
                st[clone].nxt = st[q].nxt;
                st[clone].link = st[q].link;
                while (~p && st[p].nxt.count(c) && st[p].nxt[c] == q) {
                    st[p].nxt[c] = clone;
                    p = st[p].link;
                }
                st[cur].link = clone;
                st[q].link = clone;
            }
        }
        last = cur;
    }

    ll count(int u) {
        ll &ret = dp[u];
        if (~ret)return ret;
        ret = cnt[u];
        for (auto [c,v]: st[u].nxt)ret += count(v);
        return ret;
    }

    ll count_dis(int u) {
        ll &ret = dp_dis[u];
        if (~ret)return ret;
        ret = 1;
        for (auto [c,v]: st[u].nxt)ret += count_dis(v);
        return ret;
    }

    void build() {
        vector<pair<int, int> > v;
        for (int i = 1; i <= sz; i++) {
            v.push_back({st[i].len, i});
        }
        sort(v.begin(), v.end(), greater<>());
        for (auto [len,u]: v) {
            cnt[st[u].link] += cnt[u];
            idx[st[u].link] = min(idx[st[u].link], idx[u]);
        }
        count(0);
        count_dis(0);
    }

    // number of distinct substring
    ll distinctSubstrings() {
        ll ans = 0;
        for (int i = 1; i <= sz; i++)ans += st[i].len - st[st[i].link].len;
        return ans; // or dp_dis[0]-1
    }

    pair<int, int> kthDistinct(int u, ll k, int len) {
        if (!k)return {idx[u], len};
        for (auto [c,v]: st[u].nxt) {
            if (dp_dis[v] >= k)return kthDistinct(v, k - 1, len + 1);
            k -= dp_dis[v];
        }
    }

    pair<int, int> findKth(int u, ll k, int len) {
        if (cnt[u] >= k)return {idx[u], len};
        k -= cnt[u];
        for (auto [c,v]: st[u].nxt) {
            if (dp[v] >= k)return findKth(v, k, len + 1);
            k -= dp[v];
        }
    }

    pair<int, int> kthDistinct(ll k) {
        // find [pos,len] of the kth distinct substring (0-based)
        auto [pos,len] = kthDistinct(0, k, 0);
        return {pos - len + 1, len};
    }

    pair<int, int> findKth(ll k) {
        cnt[0] = 0;
        // find [pos,len] of the kth substring (not necessary distinct) (pos is 0-based)
        auto [pos,len] = findKth(0, k, 0);
        return {pos - len + 1, len};
    }
};
