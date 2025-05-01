template<typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> info;

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void modify(int pos, int p, int pl, int pr, const T& v) {
        if (pos == pl && pos == pr) {
            info[p] = v;
            return;
        }
        int mid = pl + pr >> 1;
        if (pos <= mid) {
            modify(pos, p << 1, pl, mid, v);
        } else {
            modify(pos, p << 1 | 1, mid + 1, pr, v);
        }
        pull(p);
    }

    T query(int l, int r, int p, int pl, int pr) {
        if (l <= pl && pr <= r) {
            return info[p];
        }
        int mid = pl + pr >> 1;
        T res{};
        if (l <= mid) {
            res += query(l, r, p << 1, pl, mid);
        }
        if (r > mid) {
            res += query(l, r, p << 1 | 1, mid + 1, pr);
        }
        return res;
    }

public:
    SegmentTree() : n(0) {};
    SegmentTree(int _n) {
        n = _n;
        info.assign(_n << 2 | 1, {});
    }

    void modify(int pos, const T& v) {
        modify(pos, 1, 1, n, v);
    }

    T query(int l, int r) {
        return query(l, r, 1, 1, n);
    }
};