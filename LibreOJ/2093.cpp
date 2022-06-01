/**
 * @file 2093.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 405
#define mod 1000000007

int a[maxn];
int64_t f[2][maxn][maxn], g[maxn][maxn], h[maxn][maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[0] = a[n + 1] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int j = i, maxVal = a[i]; j <= n; maxVal = max(maxVal, a[++j]))
            if (i != 1 || j != n) f[0][i][j] = (f[0][i][j] + max(0, min(a[i - 1], a[j + 1]) - maxVal)) % mod;
    auto F = [&](int l, int r) { return (l - 1) * l / 2 + (r - l + 1) * (r - l + 2) / 2 + (n - r) * (n - r + 1) / 2; };
    for (int k = 1; k <= m; k++) {
        bool t = k & 1;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++) g[i][j] = (g[i - 1][j] + f[!t][i][j] * (i - 1)) % mod;
        for (int i = 1; i <= n; i++)
            for (int j = n; j >= i; j--) h[i][j] = (h[i][j + 1] + f[!t][i][j] * (n - j)) % mod;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++) f[t][i][j] = (f[!t][i][j] * F(i, j) + g[i - 1][j] + h[i][j + 1]) % mod;
    }
    int maxVal = 0;
    for (int i = 1; i <= n; i++) maxVal = max(maxVal, a[i]);
    int tot = maxVal * Pow(n * (n + 1) / 2, m) % mod;
    for (int i = 1; i <= n; i++) {
        int64_t ans = tot;
        for (int l = 1; l <= i; l++)
            for (int r = i; r <= n; r++) ans = (ans + mod - f[m & 1][l][r]) % mod;
        cout << ans << ' ';
    }
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}