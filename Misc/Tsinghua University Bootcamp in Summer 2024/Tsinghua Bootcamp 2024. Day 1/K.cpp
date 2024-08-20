/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 1005

int a[maxn][maxn], u[maxn][maxn], r[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j], u[i][j] = r[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        map<int, int> cnt;
        for (int j = m; j; j--) r[i][j] = cnt[a[i][j] + j]++;
    }
    for (int j = 1; j <= m; j++) {
        map<int, int> cnt;
        for (int i = n; i; i--) u[i][j] = cnt[a[i][j] + i]++;
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans += r[i][j] * u[i][j];
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}