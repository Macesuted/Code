/**
 * @file 10535.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-07
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

#define maxn 305

int a[maxn][maxn], tot[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];

    for (int j = 1; j <= m; j++) {
        map<int, int> rec;
        for (int i = 1; i <= n; i++) rec[tot[i]]++, rec[tot[i] += a[i][j]]--;
        int cur = 0, mx = 0;
        for (auto [p, v] : rec) mx = max(mx, cur += v);
        cout << mx << ' ';
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
