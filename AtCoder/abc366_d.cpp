/**
 * @file abc366_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
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

#define maxn 105

int64_t a[maxn][maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) cin >> a[i][j][k];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) a[i][j][k] += a[i][j][k - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) a[i][j][k] += a[i][j - 1][k];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) a[i][j][k] += a[i - 1][j][k];
    int q;
    cin >> q;
    while (q--) {
        int xl, xr, yl, yr, zl, zr;
        cin >> xl >> xr >> yl >> yr >> zl >> zr;
        cout << a[xr][yr][zr] - a[xl - 1][yr][zr] - a[xr][yl - 1][zr] - a[xr][yr][zl - 1] + a[xl - 1][yl - 1][zr] +
                    a[xl - 1][yr][zl - 1] + a[xr][yl - 1][zl - 1] - a[xl - 1][yl - 1][zl - 1]
             << endl;
    }
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