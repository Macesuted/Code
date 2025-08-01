/**
 * @file 2129B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-31
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

#define maxn 5005

int p[maxn], rp[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i], rp[p[i]] = i, vis[i] = true;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = rp[i], cnt = 0;
        vis[x] = false;
        for (int i = 1; i < x; i++) cnt += vis[i];
        ans += min(cnt, n - i - cnt);
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