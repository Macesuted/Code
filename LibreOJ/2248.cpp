/**
 * @file 2248.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 5005

int a[maxn][maxn], T[maxn * maxn];
bool vis[maxn][maxn];

void solve(void) {
    int64_t v, A, B, C, D;
    int n, m, q;
    cin >> v >> A >> B >> C >> D >> n >> m >> q;
    for (int i = 1; i <= n * m; i++) T[i] = i;
    for (int i = 1; i <= n * m; i++) swap(T[i], T[(v = (A * v * v + B * v + C) % D) % i + 1]);
    for (int i = 1, x, y; i <= q; i++) cin >> x >> y, swap(T[x], T[y]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = T[(i - 1) * m + j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) T[a[i][j]] = (i - 1) * m + j;
    for (int i = 1; i <= n * m; i++) {
        int x = (T[i] - 1) / m + 1, y = (T[i] - 1) % m + 1;
        if (vis[x][y]) continue;
        cout << i << ' ';
        for (int r = 1; r <= x - 1; r++)
            for (int c = y + 1; c <= m && !vis[r][c]; c++) vis[r][c] = true;
        for (int r = x + 1; r <= n; r++)
            for (int c = y - 1; c >= 1 && !vis[r][c]; c--) vis[r][c] = true;
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