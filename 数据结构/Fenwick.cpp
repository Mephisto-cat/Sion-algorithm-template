template<typename T>
struct Fenwick {
    int n;
    std::vector<T> c;

    Fenwick(int n_) {
        n = n_;
        c.assign(n_, {});
    }

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int x, const T& v) {
        for (int i = x; i < n; i += lowbit(i)) {
            c[i] = c[i] + v;
        }
    }

    T sum(int x) {
        T res {};
        for (int i = x; i >= 1; i -= lowbit(i)) {
            res = res + c[i];
        }
        return res;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // 第一个 sum(x) >= k
    int find(const T& k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i > 0; i /= 2) {
            if (x + i <= n && cur + c[x + i] <= k) {
                x += i;
                cur = cur + c[x];
            }
        }
        return x;
    }
};