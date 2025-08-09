/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    int x, b;
    cin >> x >> b;

    if (x >= b) return cout << -1 << endl, void();

    int r = b % x, t = b / x + (b % x > 0);
    if (r == 0) r = x;

    vector<int> ans;
    ans.push_back(r);
    ans.push_back(0);
    for (int i = r + 1; i < b && ans.size() < t; i++) ans.push_back(i);

    for (auto x : ans) cout << x << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}