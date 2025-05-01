template<typename T>
class ST {
public:
    int n;
    std::vector<T> a;
    std::vector<std::vector<T>> fmin, fmax, fgcd;

    ST(int _n) {
        n = _n;
        a.assign(_n + 1, {});
    };

    void cal_max() {
        fmax.assign(n + 1, std::vector<T>(std::__lg(n) + 1, {}));
        for (int i = 0; i < n; i++) {
            fmax[i][0] = a[i];
        }
        for (int j = 1; j <= std::__lg(n); j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                fmax[i][j] = std::max(fmax[i][j - 1], fmax[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    void cal_min() {
        fmin.assign(n + 1, std::vector<T>(std::__lg(n) + 1, {}));
        for (int i = 0; i < n; i++) {
            fmin[i][0] = a[i];
        }
        for (int j = 1; j <= std::__lg(n); j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                fmin[i][j] = std::min(fmin[i][j - 1], fmin[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    void cal_gcd() {
        fgcd.assign(n + 1, std::vector<T>(std::__lg(n) + 1, {}));
        for (int i = 0; i < n; i++) {
            fgcd[i][0] = a[i];
        }
        for (int j = 1; j <= std::__lg(n); j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                fgcd[i][j] = std::gcd(fgcd[i][j - 1], fgcd[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T get_max(int l, int r) {
        int len = std::__lg(r - l + 1);
        return std::max(fmax[l][len], fmax[r - (1 << len) + 1][len]);
    }

    T get_min(int l, int r) {
        int len = std::__lg(r - l + 1);
        return std::min(fmin[l][len], fmin[r - (1 << len) + 1][len]);
    }

    T get_gcd(int l, int r) {
        int len = std::__lg(r - l + 1);
        return std::gcd(fgcd[l][len], fgcd[r - (1 << len) + 1][len]);
    }
};