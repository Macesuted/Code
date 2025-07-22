/**
 * @file 101808I.cpp
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

#define maxn 105

int a[maxn];

void solve(void) {
    int n, mv = INT_MAX, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i], mv = min(mv, a[i]);
    if (n & 1) return cout << ((sum & 1) ? "Yalalov" : "Shin") << endl, void();
    cout << ((sum & 1) || (mv & 1) ? "Yalalov" : "Shin") << endl;
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