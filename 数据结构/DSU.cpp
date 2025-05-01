struct DSU {
    std::vector<int> fa, siz;

    DSU(int n) {
        init(n);
    }
    void init(int n) {
        fa.resize(n);
        siz.assign(n, 1);
        std::iota(fa.begin(), fa.end(), 0);
    }
    
    int find(int x) {
        if (x != fa[x]) {
            return fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        int tx = find(x), ty = find(y);
        if (tx == ty) {
            return false;
        }
        fa[ty] = tx;
        siz[tx] += siz[ty];
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }
};