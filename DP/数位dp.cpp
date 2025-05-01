i64 dp[14], ten[14]; // dp[i] 表示为 i 位数时每种数字有多少个，ten[i] 表示 10^i
void cal(i64 x, std::vector<i64>& cnt) {
    std::vector<int> num(1);
    while (x) {
        num.push_back(x % 10);
        x /= 10;
    }
    // 299
    for (int i = int(num.size()) - 1; i >= 1; i--) {
        // [00, 99]
        for (int j = 0; j <= 9; j++) {
            cnt[j] += dp[i - 1] * num[i];
        }
        // [000, 200) 中的 0 和 1
        for (int j = 0; j < num[i]; j++) {
            cnt[j] += ten[i - 1];
        }
        i64 num2 = 0;
        for (int j = i - 1; j >= 1; j--) {
            num2 = num2 * 10 + num[j];
        }
        // num2: 99 计算 2 在百位出现的次数
        cnt[num[i]] += num2 + 1; // cnt[2] += 99 + 1
        // 去除前导零 [00, 99]
        cnt[0] -= ten[i - 1]; // cnt[0] -= ten[3 - 1] = cnt[0] - 100
    }
}
void init() {
    ten[0] = 1;
    for (int i = 1; i <= 14; i++) {
        dp[i] = i * ten[i - 1];
        ten[i] = 10 * ten[i - 1];
    }
}