const int N = 5e5 + 10;
const int mod = 1e9 + 7;
std::vector<i64> fac(N + 1, 1), invfac(N + 1, 1);
i64 fpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}
i64 C(int n, int m) {  // 组合数
    if (m > n || m < 0) {
        return 0;
    }
    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
i64 A(int n, int m) {  // 排列数
    if (m > n || m < 0) {
        return 0;
    }
    return fac[n] * invfac[n - m] % mod;
}
i64 catalan(int n) {  // 卡特兰数
    if (n < 0) {
        return 0;
    }
    return C(2 * n, n) * fpow(n + 1, mod - 2) % mod;
}