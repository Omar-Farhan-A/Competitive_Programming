const int N=32;
struct Matrix {
    array<array<ll, N>, N> a{};
 
    static Matrix identity() {
        Matrix result;
        for (int i = 0; i < N; i++)result.a[i][i] = 1;
        return result;
    }
 
    Matrix operator *(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (a[i][k] == 0) continue;
                for (int j = 0; j < N; j++) {
                    if (other.a[k][j] == 0) continue;
                    result.a[i][j] += a[i][k] * other.a[k][j] % mod;
                    if (result.a[i][j] >= mod) {
                        result.a[i][j] -= mod;
                    }
                }
            }
        }
        return result;
    }
};
 
Matrix power(Matrix base, ll k) {
    Matrix result = Matrix::identity();
    while (k) {
        if (k & 1)result = result * base;
        base = base * base;
        k >>= 1;
    }
    return result;
}
