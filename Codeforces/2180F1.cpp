/**
 * @file 2180F1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 5005
#define mod 1'000'000'007

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

const int64_t frac14 = inv(4), frac34 = 3 * inv(4) % mod;

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }
int64_t Add(int &x, int64_t y) { return x = Mod(x + y); }

int f[maxn][maxn][2][2], g[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    cout << qpow(4, (n + 1) * (m + 1)) * g[n][m] % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++) f[1][1][x][y] = (x ? frac14 : frac34) * (y ? frac14 : frac34) % mod;

    for (int i = 1; i + 1 < maxn; i++)
        for (int j = 1; j + 1 < maxn; j++)
            for (int u = 0; u < 2; u++)
                for (int l = 0; l < 2; l++)
                    for (int t = 0; t < 4; t++) {
                        int64_t v = f[i][j][u][l] * frac14 % mod;
                        bool U = u || (t == 0), L = l || (t == 1), D = (t == 2), R = (t == 3);
                        if (!L) {
                            Add(f[i + 1][j][D][0], v * frac34 % mod);
                            Add(f[i + 1][j][D][1], v * frac14 % mod);
                        } else if (!U) {
                            Add(f[i][j + 1][0][R], v * frac34 % mod);
                            Add(f[i][j + 1][1][R], v * frac14 % mod);
                        } else
                            Add(g[i][j], v);
                    }

    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < maxn; j++) Add(g[i][j], g[i][j - 1]);
    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < maxn; j++) Add(g[i][j], g[i - 1][j]);

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
