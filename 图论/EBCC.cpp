// 用于存储 DFS 过程中经过的边（调试/分析用，不是核心必须的）
std::set<std::pair<int, int>> E;
/*
 * EBCC = Edge-Biconnected Components
 * 作用：对无向图进行 边双连通分量 分解
 * 主要用途：判桥 / 建立桥树 / 缩点分析
*/
struct EBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel; // dfn[i] = 时间戳, low[i] = 能回溯的最小时间戳 bel[i] = 节点 i 所属的 EBCC 编号
    int cur, cnt;                   // cur = 当前时间戳, cnt = EBCC 数
    
    EBCC() {}
    EBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            if (dfn[y] == -1) {
                E.emplace(x, y);
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
                E.emplace(x, y);
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    // 主接口：运行 EBCC 分解，返回 bel[]（点对应的分量编号）
    std::vector<int> work() {
        dfs(0, -1);
        return bel;
    }
    
    struct Graph {
        int n;                                  // 压缩后的点数 = 分量数
        std::vector<std::pair<int, int>> edges; // 分量间的边
        std::vector<int> siz;                   // 每个分量的点数
        std::vector<int> cnte;                  // 每个分量内部的边数
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (auto j : adj[i]) {
                if (bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                } else if (i < j) {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};