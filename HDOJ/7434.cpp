/**
 * @file 7434.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

int a[maxn], b[maxn], c[maxn], d[maxn];
int64_t f[maxn][maxn * 5];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= min(k, 4 * i); j++) f[i][j] = INT64_MAX;
    f[0][0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= min(k, 4 * i); j++)
            if (f[i][j] != INT64_MAX)
                f[i + 1][j] = min(f[i + 1][j], f[i][j]), f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j] + a[i + 1]),
                      f[i + 1][j + 2] = min(f[i + 1][j + 2], f[i][j] + b[i + 1]),
                      f[i + 1][j + 3] = min(f[i + 1][j + 3], f[i][j] + c[i + 1]),
                      f[i + 1][j + 4] = min(f[i + 1][j + 4], f[i][j] + d[i + 1]);
    cout << f[n][k] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}