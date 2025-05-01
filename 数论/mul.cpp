i64 mul(i64 a, i64 b, i64 mod) {
    i64 res = a * b - i64(1.0L * a * b / mod) * mod;
    res %= mod;
    if (res < 0) {
        res += mod;
    }
    return res;
}

