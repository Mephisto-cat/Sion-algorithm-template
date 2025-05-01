template<typename T>
struct CRT {
    int n;
    std::vector<T> a, b, c, m;
    CRT(int n_) {
        n = n_;
        a.assign(n_, {});
        b.assign(n_, {});
        c.assign(n_, {});
        m.assign(n_, {});
    }

    T exgcd(T a, T b, T &x, T &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        T g = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }

    T cal_inv(T a, T b) {
        T x, y;
        T g = exgcd(a, b, x, y);
        assert(g == 1);
        return (x % b + b) % b;
    }

    i64 mul(i64 a, i64 b, i64 mod) {
        i64 res = a * b - i64(1.0L * a * b / mod) * mod;
        res %= mod;
        if (res < 0) {
            res += mod;
        }
        return res;
    }

    T cal() {
        T M = 1;
        for (int i = 0; i < n; i++) {
            M *= m[i];
        }
        for (int i = 0; i < n; i++) {
            b[i] = M / m[i];
        }
        for (int i = 0; i < n; i++) {
            c[i] = mul(b[i], cal_inv(b[i], m[i]), M);
            c[i] %= M;
        }

        T res = 0;
        for (int i = 0; i < n; i++) {
            res += mul(c[i], a[i], M);
            res %= M;
        }
        return res;
    }
};