/**
 * @file 105586H.cpp
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

#define maxn 1000005

int a[maxn], f[maxn][4];
bool skip[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], skip[i] = false;

    f[0][0] = 0, f[0][1] = f[0][2] = f[0][3] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        for (int t = 0; t < 4; t++) f[i][t] = INT_MIN;
        if (a[i] == 0) {
            f[i][0] = f[i][1] = max({f[i - 1][0], f[i - 1][3] + 1});
        } else if (a[i] == +1) {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            f[i][1] = f[i - 1][2];
            f[i][2] = f[i - 1][3];
        } else {
            f[i][0] = max({f[i - 1][0], f[i - 1][1] + 1, f[i - 1][2] + 2, f[i - 1][3] + 3});
            f[i][3] = f[i - 1][0];
        }
    }

    int ans = max({f[n][0], f[n][1], f[n][2], f[n][3]});
    for (int i = 1; i <= n; i++) ans += a[i];

    while (q--) {
        int x;
        cin >> x;
        cout << (x <= ans ? "YES" : "NO") << endl;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}