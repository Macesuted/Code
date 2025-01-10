/**
 * @file 105586I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

#define maxn 100005

int jmp[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> jmp[i], vis[i] = false;
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int p = i;
        while (!vis[p]) vis[p] = true, p = jmp[p];
        ans++;
    }
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