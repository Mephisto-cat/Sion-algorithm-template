// 求单个欧拉函数
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res = res / i * (i - 1);
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

// 求全部数的欧拉函数
constexpr int N = 1e6;
bool isprime[N + 1];
int phi[N + 1];
std::vector<int> pri;
void get_phi(int n) {
    std::fill(isprime + 2, isprime + n + 1, true);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : pri) {
            if (i * p > n) {
                break;
            }
            isprime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}