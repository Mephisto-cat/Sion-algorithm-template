template<typename T>
struct Dijkstra {
    struct Node {
        int u;
        T w;
        bool operator < (const Node& t) const {
            return w > t.w;
        }
    };

	const int inf = 2e9;
	int n;
	Dijkstra() {}
	Dijkstra(int n) {
		init(n + 1); // 从 1 开始存储
	}

	std::vector<std::vector<std::pair<int, T>>> adj; // 邻接表存图
	std::vector<T> dis;				  // 距离
	// 初始化
	void init(int n) {
		this->n = n;
		adj.assign(n, {});
		dis.assign(n, inf);			 // 初始化为无穷大
	}

	// 加边 u v是边的顶点，w是边权
	void addEdge(int u, int v, T w) {
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	// 单源非负权最短路 s是源
	void shortest_path(int s) {
		std::vector<bool> vis(this->n);
		// 堆优化
        std::priority_queue<Node> pq;
		pq.push({s, 0});
		dis[s] = 0;

		while (!pq.empty()) {
			int u = pq.top().u;
            pq.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (auto [y, w] : adj[u]) {
				if (dis[y] > dis[u] + w) {
					dis[y] = dis[u] + w;
					pq.push({y, dis[y]});
				}
			}
		}
		// dis 已被更新
	}
};