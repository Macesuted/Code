/**
 * @file 104772F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
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

int a[maxn], b[maxn];
int f[maxn][maxn][maxn];

void dfs(int i, int j, int k) {
    if (i == 0) return;
    if (i == 1) return cout << "SC", void();
    int p = f[i][j][k];
    if (p == -1) return cout << "SC", dfs(i - 1, j + 1, k + 1);
    cout << "S";
    dfs(p, j + 1, k);
    cout << "C";
    dfs(i - p - 1, j + p + 1, k + p + 1);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i] == b[j]) f[1][i][j] = true;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j + i - 1 <= n; j++)
            for (int k = 1; k + i - 1 <= n; k++) {
                if (a[j] == b[k] && f[i - 1][j + 1][k + 1]) f[i][j][k] = -1;
                if (a[j] == b[k + i - 1] && f[i - 1][j + 1][k]) f[i][j][k] = i - 1;
                for (int p = 1; p < i - 1 && !f[i][j][k]; p++)
                    if (a[j] == b[k + p] && f[p][j + 1][k] && f[i - p - 1][j + p + 1][k + p + 1]) f[i][j][k] = p;
            }
    if (!f[n][1][1]) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    dfs(n, 1, 1);
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