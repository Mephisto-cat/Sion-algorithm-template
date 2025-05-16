struct SCC {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<int> stk, dfn, low, bel; // bel[i] 表示 i 所在的 SCC
    int cur, cnt; // cur 表示当前时间戳, cnt 表示 SCC 编号

    SCC (int n_) {
        n = n_ - 1;
        e.assign(n_, {});
        dfn.assign(n_, -1);
        low.resize(n_);
        bel.assign(n_, -1); 
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++cur;
        stk.push_back(u);

        for (auto y : e[u]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[u] = std::min(low[u], low[y]);
            } else if (bel[y] == -1) {
                low[u] = std::min(low[u], dfn[y]);
            }
        }

        if (dfn[u] == low[u]) {
            cnt++;
            while (1) {
                int k = stk.back();
                stk.pop_back();
                bel[k] = cnt;
                if (k == u) {
                    break;
                }
            }
        }
    }

    std::vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};