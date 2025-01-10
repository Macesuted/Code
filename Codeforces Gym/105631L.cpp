/**
 * @file 105631L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
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

#define maxn 1005

int64_t a[maxn], b[maxn], ans[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    int64_t A = a[1], B = 1;
    for (int i = 2; i <= n; i++) A = gcd(A, a[i]);
    for (int i = 1; i <= m; i++) {
        B = lcm(B, b[i]);
        if (A % B) return cout << "No" << endl, void();
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans[i][j] = b[j];

    if (n == 1) {
        if (A != B) return cout << "No" << endl, void();
        for (int j = 1; j <= m; j++) ans[1][j] = b[j];
    } else if (m == 1) {
        if (A != B) return cout << "No" << endl, void();
        for (int i = 1; i <= n; i++) ans[i][1] = a[i];
    } else {
        for (int i = 1; i < n; i++) ans[i][1] = a[i];
        ans[n][2] = a[n];
    }

    cout << "Yes" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << ans[i][j] << ' ';
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