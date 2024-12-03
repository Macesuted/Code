/**
 * @file 2042A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-02
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
    int n, k;
    cin >> n >> k;
    vector<int> a;
    for (int i = 1, v; i <= n; i++) cin >> v, a.push_back(v);
    sort(a.begin(), a.end());
    while (!a.empty() && a.back() <= k) k -= a.back(), a.pop_back();
    cout << k << endl;
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