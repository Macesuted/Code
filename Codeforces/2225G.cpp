/**
 * @file 2225G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int x[15];
bool vis[5005];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> x[i];

    int g = x[1];
    for (int i = 2; i <= m; i++) g = gcd(g, x[i]);

    if (g != 1) return cout << -1 << endl, void();

    sort(x + 1, x + m + 1);

    for (int i = 0; i < n; i++) vis[i] = false;

    cout << 0, vis[0] = true;

    for (int i = 1, p = 0; i < n; i++) {
        int q = 0;
        for (int j = n - 1; j > 0 && !q; j--)
            if (!((j - p) % x[1]) && !vis[j]) q = j;

        for (int i = 2; i <= m && !q; i++)
            if (!vis[p + x[i]]) q = p + x[i];

        cout << ' ' << (p = q), vis[p] = true;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
