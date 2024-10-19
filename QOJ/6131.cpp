/**
 * @file 6131.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

void solve(void) {
    int n, k;
    cin >> n >> k;
    vector<int> ans;
    for (int v = 1; v < n && k; v++) {
        bool chk = true;
        for (int i = 0; i < n && chk; i++) chk &= ((i ^ v) < n);
        if (chk) k--, ans.push_back(v);
    }
    if (k) return cout << "Impossible" << endl, void();
    for (auto i : ans) {
        for (int j = 0; j < n; j++) cout << (i ^ j) + 1 << ' ';
        cout << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}