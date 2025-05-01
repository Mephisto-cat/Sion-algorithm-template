template<class Info>
class SegmentTree {
private:
    std::vector<Info> info;
    int n;
    
    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    
    void modify(int pos, int p, int pl, int pr, const Info v) {
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
public:
    SegmentTree(int n_) {
        n = n_;
        info.assign(n_ << 2 | 1, {});
    }
    
    void modify(int pos, const Info v) {
        modify(pos, 1, 1, n, v);
    }
    
    i64 query() {
        return info[1].ans;
    }
};

class Info {
public:
    i64 ans = 0;
    i64 pre = 0;
    i64 suf = 0;
    i64 sum = 0;
};

Info operator + (const Info& x, const Info& y) {
    Info res;
    res.pre = std::max(x.pre, x.sum + y.pre);
    res.suf = std::max(y.suf, y.sum + x.suf);
    res.sum = x.sum + y.sum;
    res.ans = std::max({x.ans, y.ans, x.suf + y.pre});
    return res;
}