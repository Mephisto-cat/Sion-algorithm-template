struct DSU {
    std::vector<int> fa, siz;
    std::vector<i64> edge; // 边数

    DSU(int n) {
        init(n);
    }
    void init(int n) {
        fa.resize(n);
        siz.assign(n, 1);
        edge.assign(n, 0ll);
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
            edge[tx]++;
            return false;
        }
        fa[ty] = tx;
        siz[tx] += siz[ty];
        edge[tx] += edge[ty] + 1;
        return true;
    }

    int V(int x) {
        return siz[find(x)];
    }

    i64 E(int x) {
        return edge[find(x)];
    }
};