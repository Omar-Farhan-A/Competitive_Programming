struct Lazy_Propagation {
    vector<ll> seg;
    vector<ll> lazy;
    vector<int> nums;
    int siz=1;
    Lazy_Propagation(int n,vector<int>&nums){
        while (siz<=n)siz*=2;
        seg=vector<ll>(2*siz);
        lazy=vector<ll>(2*siz);
        this->nums=nums;
        build(1,1,siz,1,n);
    }
    void propagate(int idx, int lx, int rx) {
        if (!lazy[idx])return;
        seg[idx] += lazy[idx]*(rx-lx+1);
        if (lx != rx) {
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    ll merge(ll a, ll b) {
        return a + b;
    }
    void build(int idx, int lx, int rx,int l,int r) {
        if (lx > r || rx < l)return;
        propagate(idx, lx, rx);
        if (lx == rx) {
            seg[idx] = nums[lx - 1];
            return;
        }
        int mid = (lx + rx) >> 1;
        build(2 * idx, lx, mid,l,r);
        build(2 * idx + 1, mid + 1, rx,l,r);
        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    ll query(int idx, int lx, int rx, int l, int r) {
        propagate(idx, lx, rx);
        if (lx >= l && rx <= r) {
            return seg[idx];
        }
        int mid = (lx + rx) >> 1;
        if (l <= mid && r > mid) {
            return merge(query(idx * 2, lx, mid, l, r), query(idx * 2 + 1, mid + 1, rx, l, r));
        } else if (r <= mid) {
            return query(idx * 2, lx, mid, l, r);
        } else {
            return query(idx * 2 + 1, mid + 1, rx, l, r);
        }
    }
    ll query(int l,int r){
        return query(1,1,siz,l,r);
    }
    void update(int idx, int lx, int rx, int l, int r, ll v) {
        propagate(idx, lx, rx);
        if (lx > r || rx < l)return;
        if (lx >= l && rx <= r) {
            lazy[idx] += v;
            propagate(idx, lx, rx);
            return;
        }
        int mid = (lx + rx) >> 1;
        update(2 * idx, lx, mid, l, r, v);
        update(2 * idx + 1, mid + 1, rx, l, r, v);
        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }
    void update(int l,int r,int v){
        update(1,1,siz,l,r,v);
    }
};
