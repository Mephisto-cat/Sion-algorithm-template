using Matrix = std::vector<std::vector<i64>>;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res(a.size(), std::vector<i64> (b[0].size()));

    for (int i = 0; i < a.size(); i++) { // a 行
        for (int j = 0; j < b[0].size(); j++) { // b 列
            for (int k = 0; k < b.size(); k++) { // a 列，b 行
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
            }
        }
    }
    return res;
}

Matrix MatrixPow(Matrix a, i64 b) {
    int n = a.size();
    Matrix res(n, std::vector<i64> (n));

    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}