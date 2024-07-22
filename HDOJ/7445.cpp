/**
 * @file 7445.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef pair<int, int> pii;

void solve(void) {
    vector<pii> ans;

    int n, n1 = 1;
    cin >> n;
    for (int i = 1; i * 3 <= n; i++) {
        ans.emplace_back(min(i, 3), i + 1);
        ans.emplace_back(min(i, 2), i + 2);
        ans.emplace_back(min(i, 1), i + 3);
        n1 = i + 3;
    }
    for (int i = 0; i < n % 3; i++) ans.emplace_back(1, ++n1);
    sort(ans.begin(), ans.end());
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}