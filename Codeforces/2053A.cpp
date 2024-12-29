/**
 * @file 2053A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    vector<int> a;
    int n;
    cin >> n;
    for (int i = 0, v; i < n; i++) cin >> v, a.push_back(v);
    for (int i = 0; i < n - 1; i++)
        if (min(a[i], a[i + 1]) * 2 > max(a[i], a[i + 1])) return cout << "YES" << endl, void();
    cout << "NO" << endl;
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