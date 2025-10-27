template<typename T>
class ST {
public:
    int n;
    std::vector<T> a;
    std::vector<std::vector<T>> fmin, fmax, fgcd;

    ST(int _n) {
        n = _n;
        a.assign(n, {});
    };

    void cal_max() {
        int LOG = std::__lg(n) + 1;
        fmax.assign(n, std::vector<T>(LOG));
        for (int i = 0; i < n; i++) {
            fmax[i][0] = a[i];
        }
        for (int j = 1; j < LOG; j++) {
            int len = 1 << j;
            for (int i = 0; i + len <= n; i++) {
                fmax[i][j] = std::max(fmax[i][j - 1], fmax[i + (len >> 1)][j - 1]);
            }
        }
    }

    void cal_min() {
        int LOG = std::__lg(n) + 1;
        fmin.assign(n, std::vector<T>(LOG));
        for (int i = 0; i < n; i++) {
            fmin[i][0] = a[i];
        }
        for (int j = 1; j < LOG; j++) {
            int len = 1 << j;
            for (int i = 0; i + len <= n; i++) {
                fmin[i][j] = std::min(fmin[i][j - 1], fmin[i + (len >> 1)][j - 1]);
            }
        }
    }

    void cal_gcd() {
        int LOG = std::__lg(n) + 1;
        fgcd.assign(n, std::vector<T>(LOG));
        for (int i = 0; i < n; i++) {
            fgcd[i][0] = a[i];
        }
        for (int j = 1; j < LOG; j++) {
            int len = 1 << j;
            for (int i = 0; i + len <= n; i++) {
                fgcd[i][j] = std::gcd(fgcd[i][j - 1], fgcd[i + (len >> 1)][j - 1]);
            }
        }
    }

    T get_max(int l, int r) {
        int len = r - l + 1;
        int k = std::__lg(len);
        return std::max(fmax[l][k], fmax[r - (1 << k) + 1][k]);
    }

    T get_min(int l, int r) {
        int len = r - l + 1;
        int k = std::__lg(len);
        return std::min(fmin[l][k], fmin[r - (1 << k) + 1][k]);
    }

    T get_gcd(int l, int r) {
        int len = r - l + 1;
        int k = std::__lg(len);
        return std::gcd(fgcd[l][k], fgcd[r - (1 << k) + 1][k]);
    }
};
