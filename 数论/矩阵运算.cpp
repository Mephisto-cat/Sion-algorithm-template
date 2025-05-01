struct Matrix {
    int n;
    std::vector<std::vector<i64>> m;
    Matrix(int n_) {
        n = n_;
        m.assign(n_ + 1, std::vector<i64> (n_ + 1, 0ll));
    }
};

Matrix operator * (const Matrix& a, const Matrix& b) {
    int n = std::max(a.n, b.n);
    Matrix res(n);

    for (int i = 1; i <= n; i++) { // a 行
        for (int j = 1; j <= n; j++) { // b 列
            for (int k = 1; k <= n; k++) { // a 列，b 行
                res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j]) % p;
            }
        }
    }
    return res;
}

Matrix MatrixPow(Matrix a, i64 b) {
    int n = a.n;
    Matrix res(n);
    for (int i = 1; i <= n; i++) {
        res.m[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}