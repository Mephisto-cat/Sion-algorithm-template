// 最小值
struct Line {
    i64 a, b;
    
    Line() : a(0), b(1e18) {}
    Line(i64 a_, i64 b_) : a(a_), b(b_) {}

    i64 cal(i64 x) {
        return a * x + b;
    }
};

struct Lichao {
    int n;
    std::vector<Line> t;

    Lichao() {}
    Lichao(int n_) {
        n = n_;
        t.assign(n_ << 2, {});
    }

    void add(int u, int l, int r, Line p) {
        int mid = (l + r) >> 1;
        if (p.cal(mid) < t[u].cal(mid)) {
            std::swap(p, t[u]);
        }
        if (p.cal(l) < t[u].cal(l)) {
            add(2 * u + 1, l, mid, p);
        }
        if (p.cal(r) < t[u].cal(r)) {
            add(2 * u + 2, mid + 1, r, p);
        }
    }

    i64 query(int u, int l, int r, int x) {
        i64 cur = t[u].cal(x);
        if (l == r) {
            return cur;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return std::min(cur, query(2 * u + 1, l, mid, x));
        } else {
            return std::min(cur, query(2 * u + 2, mid + 1, r, x));
        }
    }

    void add(Line p) {
        add(0, 0, n - 1, p);
    }

    i64 query(int x) {
        return query(0, 0, n - 1, x);
    }
};