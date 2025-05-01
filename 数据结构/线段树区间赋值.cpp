template<class Info, class Tag>
class SegmentTree {
private:
    #define ls(p) (p << 1)
    #define rs(p) (p << 1 | 1)
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    
    void pull(int p) {
        info[p] = info[ls(p)] + info[rs(p)];
    }
    
    void settag(int p, Tag v) {
        if (v.agn != -2e18) {
            info[p].val = v.agn;
        }
        tag[p] = v;
    }
    
    void push(int p) {
        if (tag[p].agn != -2e18) {
            settag(ls(p), tag[p]);
            settag(rs(p), tag[p]);
            // 标记下传，消除自身标记
            tag[p].agn = -2e18;
        }
    }
    
    void build(int p, int pl, int pr) {
        if (pl == pr) {
            info[p].val = a[pl];
            return;
        }
        int mid = pl + pr >> 1;
        build(ls(p), pl, mid);
        build(rs(p), mid + 1, pr);
        pull(p);
    }
    
    void rangeModify(int l, int r, int p, int pl, int pr, const Tag v) {
        if (l <= pl && pr <= r) {
            settag(p, v);
            return;
        }
        push(p);
        int mid = pl + pr >> 1;
        if (l <= mid) {
            rangeModify(l, r, ls(p), pl, mid, v);
        }
        if (r > mid) {
            rangeModify(l, r, rs(p), mid + 1, pr, v);
        }
        pull(p);
    }
    
    Info query(int l, int r, int p, int pl, int pr) {
        if (l <= pl && pr <= r) {
            return info[p];
        }
        push(p);
        int mid = pl + pr >> 1;
        Info res {};
        if (l <= mid) {
            res = res + query(l, r, ls(p), pl, mid);
        }
        if (r > mid) {
            res = res + query(l, r, rs(p), mid + 1, pr);
        }
        return res;
    }
public:
    std::vector<i64> a;
    SegmentTree(int n_) {
        n = n_;
        info.assign(n_ << 2 | 1, {});
        tag.assign(n_ << 2 | 1, {});
        a.assign(n_ + 1, {});
    }
    // 建树
    void build() {
        build(1, 1, n);
    }
    
    // 区间修改
    void rangeModify(int l, int r, const Tag v) {
        rangeModify(l, r, 1, 1, n, v);
    }

    // 区间查询
    i64 query(int l, int r) {
        Info res = query(l, r, 1, 1, n);
        return res.val;
    }
};
struct Tag {
    i64 agn = -2e18;
};
Tag operator + (const Tag& x, const Tag& y) {
    return y;
}

struct Info {
    i64 val {};
    int sz = 1;
};
Info operator + (const Info&x, const Info& y) {
    Info res {};
    res.val = x.val + y.val;
    res.sz = x.sz + y.sz;
    return res;
}