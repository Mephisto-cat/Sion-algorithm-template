**# 算法模板**

**## 一、数据结构**

**### 1 DSU**

\``` cpp

i64 fa[size];

i64 find(i64 x) {

  if (x != fa[x]) return fa[x] = find(fa[x]);

  return fa[x];

}

\```

**### 2 带权DSU**

\``` cpp

i64 fa[size], val[size];

i64 find(i64 x) {

  if (x != fa[x]) {

​    i64 t = fa[x];

​    fa[x] = find(fa[x]);

​    val[x] += val[t];

  }

  return fa[x];

}

\```

**### 3 ST表**

\``` cpp

  vector<int> a(n + 1);

  vector<vector<int>> f(n + 1, vector<int> (__lg(n) + 1)); // f[i][j] 表示从第i项往后到第i + (1 << j) - 1项的区间最大值



  // 初始化

  for (int i = 1; i <= n; i++) {

​    cin >> a[i];

​    f[i][0] = a[i];

  }



  for (int j = 1; j <= __lg(n); j++) {

​    for (int i = 1; i + (1 << j) - 1 <= n; i++) {

​      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);

​    }

  }



  while (m--) {

​    int l, r;

​    cin >> l >> r;



​    int len = __lg(r - l + 1);

​    cout << max(f[l][len], f[r - (1 << len) + 1][len]) << '\n';

  }

\```

**### 4 树状数组**

\``` cpp

i64 c[size];

i64 lowbit(i64 x) {

  return x & (-x);

}

void update(i64 x, i64 k) {

  for (int i = x; i <= n; i += lowbit(i)) c[i] += k;

}

i64 query(i64 x) {

  i64 ans = 0;

  for (int i = x; i; i -= lowbit(i)) ans += c[i];

  return ans;

}

\```

**### 5 线段树(lazy_tag 区间乘和区间加)**

\``` cpp

constexpr int N = 1e5 + 1;



i64 a[N];

int m;

struct tag {

  i64 mul, add;

};

struct node {

  tag t;

  i64 val;

  int sz;

}segtree[N << 2];



tag operator + (const tag &t1, const tag &t2) {

  return {t1.mul * t2.mul % m, (t1.add * t2.mul + t2.add) % m};

}



void pull(int p) {

  segtree[p].val = (segtree[p << 1].val + segtree[p << 1 | 1].val) % m;

}



void build(int p, int pl, int pr) {

  segtree[p].sz = pr - pl + 1;

  segtree[p].t = {1, 0};

  if (pl == pr) {

​    segtree[p].val = a[pl];

  } else {

​    int mid = pl + pr >> 1;

​    build(p << 1, pl, mid);

​    build(p << 1 | 1, mid + 1, pr);

​    pull(p);

  }

}



void settag(int p, tag t) {

  segtree[p].t = segtree[p].t + t;

  segtree[p].val = (segtree[p].val * t.mul + t.add * segtree[p].sz) % m;

}



void push(int p) {

  if (segtree[p].t.add != 0 || segtree[p].t.mul != 1) {

​    settag(p << 1, segtree[p].t);

​    settag(p << 1 | 1, segtree[p].t);

​    segtree[p].t = {1, 0};

  }

}



void modify(int l, int r, int p, int pl, int pr, tag t) {

  if (l <= pl && pr <= r) {

​    settag(p, t);

​    return;

  }

  push(p);

  int mid = pl + pr >> 1;

  if (l <= mid) modify(l, r, p << 1, pl, mid, t);

  if (r > mid) modify(l, r, p << 1 | 1, mid + 1, pr, t);

  pull(p);

}



i64 query(int l, int r, int p, int pl, int pr) {

  if (l <= pl && pr <= r) {

​    return segtree[p].val % m;

  }

  push(p);

  int mid = pl + pr >> 1;

  i64 res = 0;

  if (l <= mid) res += query(l, r, p << 1, pl, mid);

  if (r > mid) res += query(l, r, p << 1 | 1, mid + 1, pr);

  return res % m;

}



void solve() {

  int n, q;

  std::cin >> n >> q >> m;



  for (int i = 1; i <= n; i++) {

​    std::cin >> a[i];

  }



  build(1, 1, n);

  while (q--) {

​    int op, x, y, k;

​    std::cin >> op;

​    if (op == 1) {

​      std::cin >> x >> y >> k;

​      modify(x, y, 1, 1, n, tag({k, 0}));

​    } else if (op == 2) {

​      std::cin >> x >> y >> k;

​      modify(x, y, 1, 1, n, tag({1, k}));

​    } else {

​      std::cin >> x >> y;

​      std::cout << query(x, y, 1, 1, n) << '\n';

​    }

  }

}

\```

**### 线段树单点修改+维护区间最大子段和**

\``` cpp

int a[N];



struct node {

  int t;

  int sum, ans, maxl, maxr, sz;

}segtree[N << 2];



void pull(int p) {

  segtree[p].sum = segtree[p << 1].sum + segtree[p << 1 | 1].sum;

  segtree[p].maxl = std::max(segtree[p << 1].maxl, segtree[p << 1].sum + segtree[p << 1 | 1].maxl);

  segtree[p].maxr = std::max(segtree[p << 1 | 1].maxr, segtree[p << 1 | 1].sum + segtree[p << 1].maxr);

  segtree[p].ans = std::max({segtree[p << 1].ans, segtree[p << 1 | 1].ans, segtree[p << 1].maxr + segtree[p << 1 | 1].maxl});

}



void build(int p, int pl, int pr) {

  if (pl == pr) {

​    segtree[p].sum = a[pl];

​    segtree[p].ans = a[pl];

​    segtree[p].maxl = a[pl];

​    segtree[p].maxr = a[pl];

  } else {

​    int mid = pl + pr >> 1;

​    build(p << 1, pl, mid);

​    build(p << 1 | 1, mid + 1, pr);

​    pull(p);

  }

}



void modify(int pos, int p, int pl, int pr, int t) {

  if (pos == pl && pos == pr) {

​    segtree[p].ans = segtree[p].maxl = segtree[p].maxr = segtree[p].sum = t;

​    return;

  }

  int mid = pl + pr >> 1;

  if (pos <= mid) modify(pos, p << 1, pl, mid, t);

  else modify(pos, p << 1 | 1, mid + 1, pr, t);

  pull(p);

}



node query(int l, int r, int p, int pl, int pr) {

  if (l <= pl && pr <= r) {

​    return segtree[p];

  }

  int mid = pl + pr >> 1;

  node res, lt, rt;

  lt.ans = lt.maxl = lt.maxr = rt.ans = rt.maxl = rt.maxr = -1e9;

  res.sum = lt.sum = rt.sum = 0;

  if (l <= mid) {

​    lt = query(l, r, p << 1, pl, mid);

​    res.sum += lt.sum;

  }

  if (r > mid) {

​    rt = query(l, r, p << 1 | 1, mid + 1, pr);

​    res.sum += rt.sum;

  }

  res.maxl = std::max(lt.maxl, lt.sum + rt.maxl);

  res.maxr = std::max(rt.maxr, rt.sum + lt.maxr);

  res.ans = std::max({lt.ans, rt.ans, lt.maxr + rt.maxl});

  return res;

}

\```

**## 二、数论**

**### 1 裴蜀定理**

$设 a_1, a_2, \dots, a_n 是不全为零的整数，则存在整数 x_1, x_2, \dots, x_n, 使得 a_1 x_1 + a_2 x_2 + \cdots + a_n x_n=\gcd(a_1, a_2, \dots, a_n)。$

**#### 逆定理:**

$设 a_1, a_2, \dots, a_n 是不全为零的整数，d > 0 是 a_1, a_2, \dots, a_n 的公因数，若存在整数 x_1, x_2, \dots, x_n, 使得 a_1 x_1 + a_2 x_2 + \cdots + a_n x_n=d，则 d = \gcd(a_1, a_2, \dots, a_n)。$



**### 2、组合数C(n, k) (杨辉三角递推)**

\``` cpp

  vector<vector<i64>> C(size, vector<i64> (size));

  C[0][0] = 1;

  for (int i = 1; i < size; i++) {

​    C[i][0] = 1;

​    for (int j = 1; j <= i; j++) {

​      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % q;

​    }

  }

\```

**### 3、快速幂**

\``` cpp

i64 qmi(i64 a, i64 b, i64 p) {

  i64 res = 1;

  while (b) {

​    if (b & 1) res = res * a % p;

​    a = a * a % p;

​    b >>= 1;

  }

  return res;

}

\```

**## 三、杂项**

**### 1、归并排序求逆序对**

\``` cpp

int c[size], res;

inline void ms(int l, int r, int t[]) {

  if (l == r) return;

  int mid = l + r >> 1;

  ms(l, mid, t), ms(mid + 1, r, t);

  int p1 = l, p2 = mid + 1, idx = 0;

  while (p1 <= mid && p2 <= r) {

​    if (t[p1] <= t[p2]) c[++idx] = t[p1++];

​    else {

​      res += mid - p1 + 1;

​      c[++idx] = t[p2++];

​    }

  }

  while (p1 <= mid) c[++idx] = t[p1++];

  while (p2 <= r) c[++idx] = t[p2++];

  for (int i = 1; i <= idx; i++) t[l + i - 1] = c[i];

}

\```

**### 2、__int128输入输出(注意不要关闭同步流)**

\``` cpp

__int128 read() {

  char arr[30];

  __int128 res = 0;

  scanf("%s", arr);

  for (int i = 1; i <= strlen(arr); i++) {

​    res *= 10;

​    res += arr[i]-'0';

  }

  return res;

}

void show (__int128 num) {

  if (num > 9) { show(num / 10); }

  putchar(num % 10 + '0');

}

\```

**### 3、异或哈希**

\``` cpp

  std::vector<u64> a(n + 1), pre(n + 1);

  for (int i = 1; i <= n; i++) {

​    std::cin >> a[i];

  }



  u64 max = *std::max_element(a.begin(), a.end());



  std::mt19937_64 rnd(time(0));

  std::vector<u64> code(max + 1); // max是a[i]的最大值

  for (int i = 1; i <= max; i++) {

​    code[i] = rnd();

  }



  for (int i = 1; i <= n; i++) {

​    pre[i] = pre[i - 1] ^ code[a[i]];

  }

\```



**## 四、图论**

**### 1、倍增求lca**

\```cpp

  int t = int(log(n) / log(2)) + 1;

  std::vector<std::vector<int>> f(n + 1, std::vector<int> (t + 1));



  std::vector<int> d(n + 1);

  d[s] = 1;

  std::queue<int> q;

  q.push(s);

  while (!q.empty()) {

​    int x = q.front();

​    q.pop();

​    for (auto y : e[x]) {

​      if (d[y]) continue;

​      d[y] = d[x] + 1;

​      f[y][0] = x;

​      for (int i = 1; i <= t; i++) {

​        f[y][i] = f[f[y][i - 1]][i - 1];

​      }

​      q.push(y);

​    }

  }



  auto lca = [&](int x, int y) {

​    if (d[x] > d[y]) std::swap(x, y);

​    for (int i = t; i >= 0; i--) {

​      if (d[f[y][i]] >= d[x]) {

​        y = f[y][i];

​      }

​    }

​    if (x == y) return x;

​    for (int i = t; i >= 0; i--) {

​      if (f[x][i] != f[y][i]) {

​        x = f[x][i];

​        y = f[y][i];

​      }

​    }

​    return f[x][0];

  };

\```

**### 2、树的重心**

\```cpp

  int min = inf, center = -1;

  std::vector<int> size(n + 1);

  auto dfs = [&](auto &&self, int u, int fa) -> void {

​    size[u] = 1;

​    int max = 0;

​    for (auto y : e[u]) {

​      if (y == fa) continue;

​      self(self, y, u);

​      size[u] += size[y];

​      max = std::max(max, size[y]);

​    }

​    max = std::max(max, n - size[u]);

​    if (max <= min) {

​      if (max == min) {

​        center = std::min(center, u);

​      } else {

​        center = u;

​      }

​      min = max;

​    }

  };

\```

**### 3、树的直径**

\```cpp

  // dfs 记录路径 （无法处理负权边）

  int tar = 0, max = 0;

  std::vector<int> pre(n + 1);

  auto dfs = [&](auto &&self, int u, int fa, int w, int tag) -> void {

​    if (w > max) {

​      max = w;

​      tar = u;

​    }

​    for (auto [y, ww] : e[u]) {

​      if (y == fa) continue;

​      if (tag == 1) {

​        pre[y] = u;

​      }

​      self(self, y, u, w + ww, tag);

​    }

  };

  dfs(dfs, 1, -1, 0, 0);

  int p = tar;

  tar = 0, max = 0;

  dfs(dfs, p, -1, 0, 1);

  int q = tar;



  // 树形dp

  int ans = -inf;

  std::vector<int> dis(n + 1);

  auto dp = [&](auto &&self, int u, int fa) -> void {

​    for (auto [y, w] : e[u]) {

​      if (y == fa) continue;

​      self(self, y, u);

​      ans = std::max(ans, dis[y] + dis[u] + w);

​      dis[u] = std::max(dis[u], dis[y] + w);

​    }

  };

  dp(dp, 1, -1);

\```