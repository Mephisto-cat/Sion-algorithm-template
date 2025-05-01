template<class Info, class Tag>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    std::vector<i64> a;

    SegmentTree(int n_) {
        n = n_ - 1;
        info.assign(n_ << 2, {});
        tag.assign(n_ << 2, {});
        a.assign(n_, {});
    }

    void build(int p, int pl, int pr) {
        if (pl == pr) {
            info[p].apply(a[pl]);
            return;
        }
        int mid = pl + pr >> 1;
        build(p << 1, pl, mid), build(p << 1 | 1, mid + 1, pr);
        pull(p);
    }

    void build() {
        build(1, 1, n);
    }

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        apply(p << 1, tag[p]);
        apply(p << 1 | 1, tag[p]);
        tag[p] = {};
    }

    void rangeApply(int l, int r, int p, int pl, int pr, const Tag& v) {
        if (l <= pl && pr <= r) {
            apply(p, v);
            return;
        }
        int mid = pl + pr >> 1;
        push(p);
        if (l <= mid) {
            rangeApply(l, r, p << 1, pl, mid, v);
        }
        if (r > mid) {
            rangeApply(l, r, p << 1 | 1, mid + 1, pr, v);
        }
        pull(p);
    }

    void rangeApply(int l, int r, const Tag& v) {
        rangeApply(l, r, 1, 1, n, v);
    }

    Info rangeQuery(int l, int r, int p, int pl, int pr) {
        if (l <= pl && pr <= r) {
            return info[p];
        }
        int mid = pl + pr >> 1;
        push(p);
        Info res {};
        if (l <= mid) {
            res = res + rangeQuery(l, r, p << 1, pl, mid);
        }
        if (r > mid) {
            res = res + rangeQuery(l, r, p << 1 | 1, mid + 1, pr);
        }
        return res;
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 1, 1, n);
    }
};

struct Tag {
    i64 add = 0;
    void apply(const Tag& v) {
        add = add + v.add;
    }
};

struct Info {
    i64 sum = 0, sz = 0;
    void apply(const Tag& v) {
        sum = sum + v.add * sz;
    }
    void apply(i64 v) {
        sum = v;
        sz = 1;
    }
};

Info operator + (const Info& x, const Info& y) {
    Info res {};
    res.sum = x.sum + y.sum;
    res.sz = x.sz + y.sz;
    return res;
}