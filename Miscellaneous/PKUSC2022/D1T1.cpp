/**
 * @file D1T1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005
#define maxm 55
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return a == 1 ? 1 : Pow(a, mod - 2); }

const int64_t inv1e8 = Inv(1e8);

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

int64_t w[maxm << 1], f[maxn][maxn], g[maxn][maxn], h[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = -m; i <= +m; i++) cin >> w[i + m], w[i + m] = w[i + m] * inv1e8 % mod;
    for (int j = 0; j < n; j++) {
        for (int k = j - m; k <= j + m; k++) h[j][min(max(k, 0), n)] = Mod(h[j][min(max(k, 0), n)] + w[k - j + m]);
        h[j][j] = Mod(h[j][j] + mod - 1), h[j][n + 1] = mod - 1;
    }
    for (int j = 0; j <= n; j++) {
        int64_t inv = Inv(h[j][j]);
        for (int k = j; k <= min(n, j + m); k++) h[j][k] = h[j][k] * inv % mod;
        h[j][n + 1] = h[j][n + 1] * inv % mod;
        for (int k = j + 1; k <= min(n, j + m); k++)
            if (h[k][j]) {
                h[k][n + 1] = Mod(h[k][n + 1] + mod - h[j][n + 1] * h[k][j] % mod);
                for (int t = min(n, j + m); t >= j; t--) h[k][t] = Mod(h[k][t] + mod - h[j][t] * h[k][j] % mod);
            }
    }
    for (int i = n - 1; ~i; i--) {
        for (int j = 0; j <= i; j++) {
            for (int k = j; k <= min(n, j + m); k++) g[j][k] = h[j][k];
            g[j][n + 1] = h[j][n + 1];
        }
        for (int j = i + 1; j <= min(n, i + m); j++) g[j][j] = 1, g[j][n + 1] = f[j][i];
        for (int j = min(n, i + m); j; j--)
            for (int k = max(0, j - m); k < min(i + 1, j); k++)
                if (g[k][j]) g[k][n + 1] = Mod(g[k][n + 1] + mod - g[j][n + 1] * g[k][j] % mod), g[k][j] = 0;
        for (int j = 0; j <= i; j++) f[i][j] = g[j][n + 1];
        for (int j = 0; j <= min(n, i + m); j++) g[j][j] = g[j][n + 1] = 0;
    }
    cout << f[0][0] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}