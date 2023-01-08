/**
 * @file 94.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005
#define maxlgn 20

bool a[maxn];
int f[maxlgn][maxn * 2][2];

void solve(void) {
    int n, q;
    string s;
    cin >> n >> s >> q;
    a[0] = s[0] - '0';
    for (int i = 1; i < n; i++) a[i] = (s[i] != s[i - 1]);
    for (int i = 1; i < maxlgn; i++) {
        for (int j = 0; j < n; j++) f[i][j][a[j]]++;
        for (int j = n - 1 - (1 << i); j >= 0; j--)
            for (int t = 0; t < 2; t++) f[i][j][t] += f[i][j + (1 << i)][t];
    }
    while (q--) {
        int l, r, ans = 0;
        cin >> l >> r;
        for (int i = 1; l + (1 << (i - 1)) <= r; i++) {
            int d = 1 << i, p = l + (d >> 1);
            ans += min(f[i][p][0] - f[i][r - (r - p) % d + d][0], f[i][p][1] - f[i][r - (r - p) % d + d][1]);
        }
        cout << (ans + 1) / 2 << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("bit.in", "r", stdin), freopen("bit.out", "w", stdout);
#endif
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