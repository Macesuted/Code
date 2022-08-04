/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 16
#define mod 1000000007

typedef pair<int, int> pii;

pii a[maxn];
int d[maxn];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

int inv[18];

long long C(int n, int m) {
    long long ans = 1;
    for (int i = n; i > n - m; i--) ans = ans * i % mod;
    for (int i = m; i; i--) ans = ans * inv[i] % mod;
    return ans;
}
inline long long choose(int n, int m) { return C(n + m - 1, m - 1); }

void solve(void) {
    int k1 = read<int>();
    for (int i = 0; i < k1; i++) {
        int l = read<int>(), r = read<int>();
        a[i] = {-r, -l};
    }
    int k2 = read<int>();
    for (int i = 0; i < k2; i++) {
        int l = read<int>(), r = read<int>();
        a[k1 + i] = {l, r};
    }
    int n = k1 + k2, v = 0;
    long long all = 1;
    for (int i = 0; i < n; i++) v -= a[i].first, d[i] = a[i].second - a[i].first + 1, all = all * d[i] % mod;
    all = Pow(all, mod - 2);
    long long ans1 = 0, ans2 = 0;
    for (int S = 0; S < (1 << n); S++) {
        int t = v, id = 1;
        for (int i = 0; i < n; i++)
            if (S >> i & 1) t -= d[i], id = -id;
        if (t - 1 >= 0) ans1 = (ans1 + id * choose(t - 1, n + 1)) % mod;
        if (t >= 0) ans2 = (ans2 + id * choose(t, n)) % mod;
    }
    ans1 = (ans1 + mod) * all % mod, ans2 = (ans2 + mod) * all % mod;
    int ans3 = (1 - ans1 - ans2 + mod * 2) % mod;
    cout << ans1 << ' ' << ans2 << ' ' << ans3 << endl;
    return;
}

int main() {
    inv[0] = 1;
    for (int i = 1; i <= 17; i++) inv[i] = Pow(i, mod - 2);
    ios::sync_with_stdio(false);
    int _ = read<int>();
    while (_--) solve();
    return 0;
}