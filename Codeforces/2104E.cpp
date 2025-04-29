/**
 * @file 2104E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-28
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

#define maxn 1000005

int nxt[maxn][26], f[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s, s = ' ' + s;

    f[n + 1] = 0;
    f[n] = 1;
    for (int i = 0; i < k; i++) nxt[n][i] = nxt[n + 1][i] = n + 1;
    for (int i = n - 1; ~i; i--) {
        for (int j = 0; j < k; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;

        f[i] = INT_MAX;
        for (int j = 0; j < k; j++) f[i] = min(f[i], f[nxt[i][j]] + 1);
    }

    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int p = 0;
        for (char c : t) p = nxt[p][c - 'a'];
        cout << f[p] << endl;
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