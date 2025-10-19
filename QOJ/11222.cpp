/**
 * @file 11222.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-19
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
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            cout << i << ' ' << j << ' ';
            cout << 1 << ' ' << j << ' ' << i << ' ';
            cout << 2 << ' ' << j << ' ' << i << endl;
        }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ":" << endl, solve();

    return 0;
}
