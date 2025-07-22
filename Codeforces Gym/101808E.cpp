/**
 * @file 101808E.cpp
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

int up[maxn], x[maxn], y[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];

    for (int i = 1; i <= n; i++) up[i] = 1e6;
    for (int i = 1, u = 0; i <= n; i++) up[i] = min(up[i], u = max(u, y[i]));
    for (int i = n, u = 0; i >= 1; i--) up[i] = min(up[i], u = max(u, y[i]));

    double ans = 0;
    for (int i = 1; i < n; i++) {
        int u = min(up[i], up[i + 1]);
        if (u == min(y[i], y[i + 1])) continue;
        if (u < max(y[i], y[i + 1]))
            ans += double(x[i + 1] - x[i]) / abs(y[i + 1] - y[i]) * pow(u - min(y[i], y[i + 1]), 2) / 2;
        else
            ans += double(x[i + 1] - x[i]) * (2 * u - y[i] - y[i + 1]) / 2;
    }
    cout << fixed << setprecision(8) << ans << endl;
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