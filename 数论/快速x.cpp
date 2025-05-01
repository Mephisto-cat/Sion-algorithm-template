// 快速乘
i64 mul(i64 a, i64 b, i64 mod) {
    i64 res = a * b - i64(1.0L * a * b / mod) * mod;
    res %= mod;
    if (res < 0) {
        res += mod;
    }
    return res;
}

i64 fpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}