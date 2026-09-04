template<typename T=int>
struct Range_BIT {
    vector<T> M, C;
    int n;

    Range_BIT(int _n) : n(_n + 5) {
        M.assign(n, 0);
        C.assign(n, 0);
    }

    void add(vector<T> &bit, int i, T x) {
        for (++i; i < n; i += (i & -i))
            bit[i] += x;
    }

    void add(int l, int r, T x) {
        add(M, l, x);
        add(M, r + 1, -x);
        add(C, l, x * (l - 1));
        add(C, r + 1, -x * r);
    }

    T query(vector<T> &bit, int i) {
        T ret = 0;
        for (++i; i; i -= (i & -i))
            ret += bit[i];
        return ret;
    }

    T query(int i) {
        return query(M, i) * i - query(C, i);
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
