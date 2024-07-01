/**
 * @file 1987F2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 805

int a[maxn], f[maxn][maxn], g[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= i; j++) f[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) g[i][j] = INT_MAX;

    for (int len = 2; len <= n; len += 2)
        for (int l = 1, r = len; r <= n; l++, r++)
            if (a[l] <= l && (l - a[l]) % 2 == 0) {
                int t = (l - a[l]) / 2;
                for (int p = l + 1; p <= r; p += 2)
                    if (g[l + 1][p - 1] <= t) g[l][r] = min(g[l][r], max({t, g[p + 1][r] - (p - l + 1) / 2}));
            }

    for (int i = n; i; i--)
        for (int j = i; j >= 1; j -= 2) {
            f[i][j] = f[i + 1][j + 1];
            if (j <= a[i] && a[i] <= i && (i - a[i]) % 2 == 0) {
                int t = (i - a[i]) / 2;
                for (int p = i + 1; p <= n; p += 2)
                    if (g[i + 1][p - 1] <= t) f[i][j] = max(f[i][j], f[p + 1][j] + (p - i + 1) / 2);
            }
        }

    cout << f[1][1] << endl;

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