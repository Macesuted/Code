/**
 * @file 1987D.cpp
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

#define maxn 5005

int a[maxn], cnt[maxn], f[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;

    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++) f[i][j] = 1e9;

    f[1][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++)
            if (f[i][j] != (int)1e9) {
                if (cnt[i]) f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j] + 1);
                if (j >= cnt[i]) f[i + 1][j - cnt[i]] = min(f[i + 1][j - cnt[i]], f[i][j]);
            }
    }
    int ans = INT_MAX;
    for (int j = 0; j <= n + 1; j++) ans = min(ans, f[n + 1][j]);
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