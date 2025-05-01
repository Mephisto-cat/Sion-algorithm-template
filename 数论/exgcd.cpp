i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

i64 cal_inv(i64 a, i64 b) {
    i64 x, y;
    i64 g = exgcd(a, b, x, y);
    assert(g == 1);
    return (x % b + b) % b;
}