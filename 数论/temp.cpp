/*
@Author: oyasumi_sion
*/
#include <bits/stdc++.h>

using i64 = long long;

#define debug1(x) std::cerr << "in ["; for (auto i : x) std::cerr << i << ", "; std::cerr << "]\n";
#define debug2(x) std::cerr << #x << ": " << (x) << '\n';
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res = res / i * (i - 1);
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res; 
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::lcm(phi(5), std::lcm(phi(5), phi(81))) << '\n';

    return 0;
}