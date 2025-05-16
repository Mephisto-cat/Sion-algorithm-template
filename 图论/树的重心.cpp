    std::vector<int> p(n), dep(n), siz(n), in(n), ord(n);
    int cur = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        siz[u] = 1;
        in[u] = cur++;
        ord[in[u]] = u;
        for (auto v : e[u]) {
            if (v == p[u]) {
                continue;
            }
            p[v] = u;
            dep[v] = dep[u] + 1;
            self(self, v);
            siz[u] += siz[v];
        }
    };

    p[0] = -1;
    dfs(dfs, 0);

    auto find = [&](auto&& self, int u) -> int {
        for (auto v : e[u]) {
            if (v == p[u] || 2 * siz[v] <= n) {
                continue;
            }
            return self(self, v);
        }
        return u;
    };

    int rt = find(find, 0);
    dep[rt] = 0;
    p[rt] = -1;
    cur = 0;
    dfs(dfs, rt);