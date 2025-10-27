    std::vector<int> dis, fa;
    auto bfs = [&](int s) -> int {
        dis.assign(n, -1);
        fa.assign(n, -1);

        std::queue<int> q;
        q.push(s);
        dis[s] = 0;

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : adj[u]) {
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    fa[v] = u;
                    q.push(v);
                }
            }
        }

        // 最大 dis 索引
        return std::max_element(dis.begin(), dis.end()) - dis.begin();
    };