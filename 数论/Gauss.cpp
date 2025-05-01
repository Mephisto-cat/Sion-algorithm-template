struct Gauss {
    int n;
    std::vector<std::vector<double>> a;
    int rank; // 系数矩阵的秩
    double eps = 1e-7;

    Gauss(int n_) {
        n = n_;
        a.assign(n_, std::vector<double> (n_ + 1, {}));
    }

    int cal() {
        rank = 0;
        int col = 0; // 新增列跟踪变量
    
        for (int row = 0; row < n && col < n; col++) {
            // 1. 找当前col列的主元
            int max = row;
            for (int i = row; i < n; i++) {
                if (fabs(a[i][col]) > fabs(a[max][col])) {
                    max = i;
                }
            }
            // 2. 跳过全零列
            if (fabs(a[max][col]) < eps) {
                continue; // 修复括号错误
            }
            // 3. 交换行
            std::swap(a[row], a[max]);
            // 4. 归一化当前行（针对col列）
            double pivot = a[row][col];
            for (int j = col; j <= n; j++) { // 从col开始
                a[row][j] /= pivot;
            }
            // 5. 消去其他行（仅处理非当前行）
            for (int j = 0; j < n; j++) {
                if (j != row && fabs(a[j][col]) > eps) {
                    double factor = a[j][col];
                    for (int k = col; k <= n; k++) {
                        a[j][k] -= factor * a[row][k];
                    }
                }
            }
            row++; // 只有找到有效主元才增加行
            rank++; // 正确统计有效主元数
        }
        // 检查无解（后续行的常数项非零）
        for (int i = rank; i < n; i++) {
            if (fabs(a[i][n]) > eps) {
                return 0;
            }
        }
        // 2 无穷多解
        // 1 唯一解
        return (rank == n) ? 1 : 2;
    }
};