### 9、 SPFA O(nm)
```cpp
    for (int i = 0; i < n; i++) {
        adj[n].push_back({i, 0ll});
    }

    std::vector<i64> dis(n + 1, inf);
    auto spfa = [&]() -> bool {
        dis[n] = 0;
        std::queue<int> q;
        q.push(n);
        // cnt【u]: 到 u 的最短路经过的边数，vis[u]：u 是否在队列中
        std::vector<int> cnt(n + 1), vis(n + 1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (auto [v, w] : adj[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] > n) {
                        return false;
                    }
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return true;
    };