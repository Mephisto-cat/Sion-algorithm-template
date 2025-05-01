template<class Info, class Tag>
class SegmentTree {
private:
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void settag(int p, Tag v) {
        info[p].sum = info[p].sz - info[p].sum;
        tag[p] = tag[p] + v;
    }

    void push(int p) {
        if (tag[p].val) {
            settag(p << 1, tag[p]);
            settag(p << 1 | 1, tag[p]);
            tag[p] = {};
        }
    }

    void build(int p, int pl, int pr) {
        if (pl == pr) {
            info[p].sum = a[pl];
            return;
        }
        int mid = pl + pr >> 1;
        build(p << 1, pl, mid);
        build(p << 1 | 1, mid + 1, pr);
        pull(p);
    }

    void rangeModify(int l, int r, int p, int pl, int pr, Tag v) {
        if (l <= pl && pr <= r) {
            settag(p, v);
            return;
        }
        push(p);
        int mid = pl + pr >> 1;
        if (l <= mid) {
            rangeModify(l, r, p << 1, pl, mid, v);
        }
        if (r > mid) {
            rangeModify(l, r, p << 1 | 1, mid + 1, pr, v);
        }
        pull(p);
    }

    int query(int k, int p, int pl, int pr) {
        if (pl == pr) {
            return pl;
        }
        push(p);
        int mid = pl + pr >> 1;
        if (info[p << 1].sum >= k) {
            return query(k, p << 1, pl, mid);
        } else {
            return query(k - info[p << 1].sum, p << 1 | 1, mid + 1, pr);
        }
    }
public:
    std::vector<i64> a;
    SegmentTree(int n_) {
        n = n_;
        info.assign(n_ << 2 | 1, {});
        tag.assign(n_ << 2 | 1,  {});
        a.assign(n_ + 1,  {});
    }

    void build() {
        build(1, 1, n);
    }

    void rangeModify(int l, int r, Tag v) {
        rangeModify(l, r, 1, 1, n, v);
    }

    int query(int k) {
        return query(k, 1, 1, n);
    }
};
struct Info {
    i64 sz = 1;
    i64 sum = 0;
};
Info operator + (const Info& x, const Info& y) {
    Info res {};
    res.sz = x.sz + y.sz;
    res.sum = x.sum + y.sum;
    return res;
}
struct Tag {
    i64 val = 0;
};
Tag operator + (const Tag& x, const Tag& y) {
    Tag res {};
    int s = x.val + y.val;
    res.val = (s == 1);
    return res;
}