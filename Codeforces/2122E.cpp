/**
 * @file 2122E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-19
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

#define maxn 505
#define mod 998244353

int a[3][maxn];
int64_t f[maxn][maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) f[i][j] = 0;

    f[n][0] = 1;
    for (int i = n - 1; i >= 1; i--) {
        vector<int> cnt(k * 2 + 1, 0);
        for (int d = (a[2][i] == -1 ? 1 : a[2][i]); d <= (a[2][i] == -1 ? k : a[2][i]); d++)
            for (int u = (a[1][i + 1] == -1 ? 1 : a[1][i + 1]); u <= (a[1][i + 1] == -1 ? k : a[1][i + 1]); u++)
                cnt[d - u + k]++;

        for (int v = -k; v <= 0; v++)
            for (int j = 0; j <= k; j++) f[i][min(k, -v + j)] = (f[i][min(k, -v + j)] + f[i + 1][j] * cnt[v + k]) % mod;

        int64_t pre = f[i + 1][0];
        for (int v = 1; v <= +k; v++) pre = Mod(pre + f[i + 1][v]), f[i][0] = (f[i][0] + pre * cnt[v + k]) % mod;
    }

    int64_t ans = 0;
    for (int i = 0; i <= k; i++) ans = Mod(ans + f[1][i]);
    if (a[1][1] == -1) ans = ans * k % mod;
    if (a[2][n] == -1) ans = ans * k % mod;
    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}