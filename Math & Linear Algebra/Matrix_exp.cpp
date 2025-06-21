struct Matrix {
    vector<vector<ll>> a;
 
    Matrix(vector<vector<ll>> init = {}) {
        a = init;
    }
 
    Matrix operator*(Matrix other) {
        int n = a.size(), m = other.a[0].size(), g = other.a.size();
        vector<vector<ll>> product(n, vector<ll>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < g; k++) {
                    (product[i][j] += a[i][k] * other.a[k][j]) %= MOD;
                }
            }
        }
        return product;
    }
};
 
Matrix fast_exp(Matrix m, ll p) {
    int n = m.a.size();
    vector<vector<ll>> init(n, vector<ll>(n));
    Matrix product(init);
    for (int i = 0; i < n; i++) {
        product.a[i][i] = 1;
    }
    while (p) {
        if (p & 1) {
            product = product * m;
        }
        m = m * m;
        p >>= 1;
    }
    return product;
}
