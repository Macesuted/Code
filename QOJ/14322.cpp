/**
 * @file 14322.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005
#define mod 998244353

mt19937 rnd(114514);

int64_t a[maxn][maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int query(int s, int t, int c) {
    cout << "? " << s << ' ' << t << ' ' << c << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y;

    if (n == 1) {
        cout << "!" << endl;
        int k;
        cin >> k;
        cout << 0 << endl;
        return;
    }

    for (int i = 1; i < n; i++) {
        int64_t b = rnd() % mod, v = b;
        while (b == 0) b = rnd() % mod;
        for (int j = 1; j < n; j++, v = v * b % mod) a[i][j] = v;
        a[i][n] = query(1, n, b);
    }

    for (int i = 1; i < n; i++) {
        int p = i;
        while (p < n && a[p][i] == 0) p++;
        assert(p < n);
        for (int j = 1; j <= n; j++) swap(a[p][j], a[i][j]);
        int64_t d = inv(a[i][i]);
        for (int j = i; j <= n; j++) a[i][j] = a[i][j] * d % mod;
        for (int j = 1; j < n; j++) {
            if (j == i || a[j][i] == 0) continue;
            for (int k = n; k >= i; k--) a[j][k] = (a[j][k] + mod - a[j][i] * a[i][k] % mod) % mod;
        }
    }

    cout << "!" << endl;
    int k;
    cin >> k;
    int64_t ans = 0, v = k;
    for (int i = 1; i < n; i++, v = v * k % mod) ans = (ans + a[i][n] * v) % mod;
    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}