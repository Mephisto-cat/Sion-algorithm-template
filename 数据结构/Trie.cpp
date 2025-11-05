const int N = 1e6 + 1;

int tree[N][26]; // 每个节点有 26 条指向子节点的边（a..z）
int cnt[N];      // 每个节点的终止单词计数（到此为止有多少单词以该节点结尾）
int passcnt[N];  // 经过该节点的单词数（用于 LCP）
int tot; // 当前已分配的节点数（节点编号从 1 开始）

// 根是 1
// 分配一个新节点（++tot），把 tree[x][*] 设为 0，cnt[x]=0。返回新节点索引。 
int newNode() {
    int x = ++tot;
    for (int i = 0; i < 26; i++) {
        tree[x][i] = 0;
    }
    cnt[x] = 0;
    passcnt[x] = 0;
    return x;
}

void init() {
    tot = 0;
    newNode();
}

/* 从根 p=1 出发，对字符串每个字符 i 做 x = i - 'a'：
若 tree[p][x] == 0 则创建新节点；
移动到 p = tree[p][x]。
最后在终点 cnt[p]++，表示该单词出现次数增加 1。
复杂度：O(|s|)（字符长度）。
*/
void insert(std::string s) {
    int p = 1;
    passcnt[p]++;
    for (auto i : s) {
        int x = i - 'a';
        if (!tree[p][x]) {
            tree[p][x] = newNode();
        }
        p = tree[p][x];
        passcnt[p]++;
    }
    cnt[p]++;
}

// 返回值是节点索引 p（若存在该串对应节点），否则返回 0。
int query(std::string s) {
    int p = 1;
    for (auto i : s) {
        int x = i - 'a';
        if (tree[p][x]) {
            p = tree[p][x];
        } else {
            return 0;
        }
    }
    return p;
}

// 删除 s，但是不修改 cnt
void del(const std::string &s) {
    int p = 1;
    passcnt[p]--;
    for (char ch : s) {
        int x = ch - 'a';
        p = tree[p][x];
        passcnt[p]--;
    }
}

std::string lcp_res;
void dfs_lcp(int p, std::string &cur, int num) {
    for (int x = 0; x < 26; x++) {
        int v = tree[p][x];
        if (!v || passcnt[v] < num) continue;
        cur.push_back(char('a' + x));
        if (cur.size() > lcp_res.size()) {
            lcp_res = cur;
        }
        dfs_lcp(v, cur, num);
        cur.pop_back();
    }
}

// 返回最长公共前缀（所有 num 个字符串共有）
std::string lcp(int num) {
    lcp_res = "";
    std::string cur;
    dfs_lcp(1, cur, num);
    return lcp_res;
}