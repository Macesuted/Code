/**
 * @file 105481J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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

int x[maxn], y[maxn];

void solve(void) {
    int n, A, B, C, D;
    cin >> n >> A >> B >> C;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    cin >> D;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (x[i] + y[i] < C) x[i] += D, x[i] = min(x[i], A), ans += (x[i] + y[i] >= C);
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}