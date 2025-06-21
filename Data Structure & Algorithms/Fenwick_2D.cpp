class BIT2D {
private:
    vector<vector<int>> bit;
    int n, m;
public:
    BIT2D(int n, int m) {
        this->n = n + 5;
        this->m = m + 5;
        bit = vector<vector<int>>(n + 5, vector<int>(m + 5));
    }

    void add(int r, int c, int v) {
        for (int i = r; i < n; i += i & -i) {
            for (int j = c; j < m; j += j & -j) {
                bit[i][j] += v;
            }
        }
    }

    int query(int r, int c) {
        int ret = 0;
        for (int i = r; i > 0; i -= i & -i) {
            for (int j = c; j > 0; j -= j & -j) {
                ret += bit[i][j];
            }
        }
        return ret;
    }

    int query(int r, int c, int r2, int c2) {
        return query(r2, c2) - query(r2, c - 1) - query(r - 1, c2) + query(r - 1, c - 1);
    }
};
