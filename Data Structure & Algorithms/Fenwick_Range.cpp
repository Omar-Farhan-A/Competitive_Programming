template<typename T = int>
struct Fenwick_Tree_Range {
    int N;
    T DEFAULT;
    vector<T> M, C;
    Fenwick_Tree_Range(int sz = 0) {
        N = sz + 1, DEFAULT = 0;
        M = C = vector<T>(N + 10);
    }
    int lowest_bit(int idx) {
        return (idx & -idx);
    }

    void build(vector<T> &nums) {
        for (int i = 0; i < sz(nums); i++)
            add(i, i, nums[i]);
    }
    void add_range(int idx, T addM, T addC) {
        idx++;
        while (idx <= N) {
            M[idx] += addM;
            C[idx] += addC;
            idx += lowest_bit(idx);
        }
    }
    void add(int l, int r, T val) {
        add_range(l, val, -val * (l - 1));
        add_range(r + 1, -val, val * r);
    }

    void add(int idx, T val) {
        add(idx, idx, val);
    }
    T get(int idx) {
        T ans = DEFAULT;
        int pos = idx++;
        while (idx) {
            ans += pos * M[idx] + C[idx];
            idx -= lowest_bit(idx);
        }
        return ans;
    }
    T query(int L, int R) {
        if (L > R) return DEFAULT;
        return get(R) - get(L - 1);
    }
};
