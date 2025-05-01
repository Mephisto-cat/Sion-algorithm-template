const int N = 5e5 + 1;

int tree[N][26];
int cnt[N];
int tot;

int newNode() {
    int x = ++tot;
    for (int i = 0; i < 26; i++) {
        tree[x][i] = 0;
    }
    cnt[x] = 0;
    return x;
}

void init() {
    tot = 0;
    newNode();
}

void insert(std::string s) {
    int p = 1;
    for (auto i : s) {
        int x = i - 'a';
        if (!tree[p][x]) {
            tree[p][x] = newNode();
        }
        p = tree[p][x];
    }
    cnt[p]++;
}

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