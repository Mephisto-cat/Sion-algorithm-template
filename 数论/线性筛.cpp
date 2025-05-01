// minp[i] 表示 i 除了 1 以外的最小除数（一定是个素数）
// minp[i] 为 0 表示 i 是素数
// pri 中存储了所有的 素数
constexpr int N = 4e5 + 1;
int minp[N];
std::vector<int> pri;
void sieve(int n) {
    minp[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            pri.push_back(i);
        }
        for (auto j : pri) {
            if (i * j > n) break;
            minp[i * j] = j;
            if (i % j == 0) break;
        }
    }
}