/**
 * @file 2598.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n;
    cin >> n;

    if (n == 1) return cout << "NO" << endl, void();

    vector<vector<int>> a(1 << n, vector<int>(1 << n));

    for (int i = 0, cnt = 0; i < (1 << n); i++)
        for (int j = 0; j < (1 << n); j++) a[i][j] = ++cnt;

    for (int i = 0; i < (1 << n); i += 2)
        for (int j = 0; j < (1 << (n - 1)); j++) swap(a[i][j], a[i][j | (1 << (n - 1))]);

    for (int i = 0; i < (1 << (n - 1)); i++)
        for (int j = 0; j < (1 << n); j += 2) swap(a[i][j], a[i | (1 << (n - 1))][j]);

    cout << "YES" << endl;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) cout << a[i][j] << ' ';
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
