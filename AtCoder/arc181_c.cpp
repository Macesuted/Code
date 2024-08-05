/**
 * @file arc181_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-04
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

#define maxn 505

int p[maxn], q[maxn], a[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> q[i];
    for (int i = 1; i <= n; i++)
        for (int j = n - i + 1; j <= n; j++) a[p[i]][q[j]] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << a[i][j];
        cout << endl;
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