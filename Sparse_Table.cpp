struct Sparse_table {
    vector<vector<int>> S;
    vector<int> bin_log, a;
    int n;

    void build() {
        int cur_log = 0;
        for (int i = 0; i < n; i++) {
            S[i][0] = a[i];
            if ((1 << (cur_log + 1)) <= i + 1)cur_log++;
            bin_log[i + 1] = cur_log;
        }
        for (int k = 1; k < 20; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                S[i][k] = min(S[i][k - 1], S[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int query(int L, int R) {
        int k = bin_log[R - L + 1];
        return min(S[L][k], S[R - (1 << k) + 1][k]);
    }

    Sparse_table(int n, vector<int> &a) {
        S = vector<vector<int>>(n, vector<int>(20));
        bin_log.resize(n + 5);
        this->a = a;
        this->n = n;
        build();
    }

};
