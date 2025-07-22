/**
 * @file 101808C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

int rec[maxn];

void solve(void) {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = n / 2;
    s = ' ' + s, t = ' ' + t;
    if (s[m + 1] != t[m + 1]) return cout << -1 << endl, void();
    for (int i = 1; i <= m; i++) rec[i] = 0;
    for (int l = 1, r = n; l < r; l++, r--) {
        if (s[l] == t[l] && s[r] == t[r]) rec[l] |= 1;
        if (s[l] == t[r] && s[r] == t[l]) rec[l] |= 2;
        if (!rec[l]) return cout << -1 << endl, void();
    }
    int f[2] = {0, 1};
    for (int i = 1; i <= m; i++) {
        int g[2];
        g[0] = g[1] = 1e9;
        if (rec[i] & 1) g[0] = min(f[0], f[1] + 1);
        if (rec[i] & 2) g[1] = min(f[1], f[0] + 1);
        f[0] = g[0], f[1] = g[1];
    }
    cout << min(f[0], f[1]) << endl;
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