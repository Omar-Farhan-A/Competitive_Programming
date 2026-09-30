using i128 = __int128_t;

struct line {
    ll m, c;

    line(ll a = 0, ll b = 0) {
        m = a;
        c = b;
    }
};

bool bad(line l1, line l2, line l3) {
    // x12 <= x23
    return i128(l2.c - l1.c) * (l2.m - l3.m) <= i128(l3.c - l2.c) * (l1.m - l2.m);
}

struct CHT {
    // lines must be added in increasing order of slope
    deque<line> dq;

    void add(ll m, ll c) {
        line l(m, c);
        while (sz(dq) >= 2) {
            if (!bad(dq[sz(dq) - 2], dq[sz(dq) - 1], l))break;
            dq.pop_back();
        }
        dq.push_back(l);
    }

    ll subst(int i, ll x) {
        return dq[i].m * x + dq[i].c;
    }

    ll query(ll x) {
        int l = 0, r = sz(dq) - 1;
        ll ans = 0;
        while (l <= r) {
            int mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
            if (subst(mid1, x) <= subst(mid2, x)) {
                ans = subst(mid1, x);
                r = mid2 - 1;
            } else {
                ans = subst(mid2, x);
                l = mid1 + 1;
            }
        }
        return ans;
    }

    // ll query(ll x) {
    //     // queries of x must be in non-increasing order
    //     while (sz(dq) > 1) {
    //         if (subst(0, x) < subst(1, x))break;
    //         dq.pop_front();
    //     }
    //     return subst(0, x);
    // }
};
