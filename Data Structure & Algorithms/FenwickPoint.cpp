template<typename T = int>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n_) : n(n_), bit(n) {};

    void add(int i, T x) {
        for (++i; i < n; i += (i & -i))
            bit[i] += x;
    }

    T query(int i) {
        T ret = 0;
        for (++i; i; i -= (i & -i))
            ret += bit[i];
        return ret;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

};
