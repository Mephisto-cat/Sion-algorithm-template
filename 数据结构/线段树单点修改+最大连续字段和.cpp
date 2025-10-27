template<class Info>
class SegmentTree {
private:
    std::vector<Info> info;
    int n;
    
    void pull(int p) {
        info[p] = info[p * 2 + 1] + info[p * 2 + 2];
    }
    
    void modify(int pos, int p, int pl, int pr, const Info v) {
        if (pos == pl && pos == pr) {
            info[p] = v;
            return;
        }
        int mid = pl + pr >> 1;
        if (pos <= mid) {
            modify(pos, p * 2 + 1, pl, mid, v);
        } else {
            modify(pos, p * 2 + 2, mid + 1, pr, v);
        }
        pull(p);
    }

    Info query(int l, int r, int p, int pl, int pr) {
        if (l <= pl && pr <= r){
            return info[p];
        }
        int mid = pl + pr >> 1;
        Info res {};
        if (l <= mid) {
            res = res + query(l, r, p * 2 + 1, pl, mid);
        }
        if (r > mid) {
            res = res + query(l, r, p * 2 + 2, mid + 1, pr);
        }
        return res;
    }
public:
    SegmentTree(int n_) {
        n = n_;
        info.assign(n_ << 2 | 1, {});
    }
    
    void modify(int pos, const Info v) {
        modify(pos, 0, 0, n, v);
    }
    
    i64 query_pre(int l, int r) {
        return query(l, r, 0, 0, n).pre;
    }
    i64 query_suf(int l, int r) {
        return query(l, r, 0, 0, n).suf;
    }
};

struct Info {
    i64 ans = 0;
    i64 pre = 0;
    i64 suf = 0;
    i64 sum = 0;
};

Info operator + (const Info& x, const Info& y) {
    Info res {};
    res.pre = std::max(x.pre, x.sum + y.pre);
    res.suf = std::max(y.suf, y.sum + x.suf);
    res.sum = x.sum + y.sum;
    res.ans = std::max({x.ans, y.ans, x.suf + y.pre});
    return res;
}