/**
 * @file 2066A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-11
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

#define maxn 200005

int a[maxn], pos[maxn];
bool vis[maxn];

int query(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    int v;
    cin >> v;
    return v;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], vis[i] = false, pos[a[i]] = i;
    for (int i = 1; i <= n; i++) vis[a[i]] = true;

    int p = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) p = i;

    if (p) {
        int v = query(p, p % n + 1);
        return cout << "! "
                    << "AB"[v > 0] << endl,
               void();
    }

    int v = query(pos[1], pos[n]), w = query(pos[n], pos[1]);
    cout << "! "
         << "AB"[v >= n - 1 && w >= n - 1] << endl;
    return;
}

bool mem2;

int main() {
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