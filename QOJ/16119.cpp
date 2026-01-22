/**
 * @file 16119.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int k;
    cin >> k;
    int n = 2 * k + 1;

    vector<vector<int>> ans(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if ((j - i) & 1)
                ans[j].push_back(i);
            else
                ans[i].push_back(j);

    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        for (auto j : ans[i]) cout << j << ' ';
        cout << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
