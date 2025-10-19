/**
 * @file 14551.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n, m;
    cin >> n >> m;
    int x = (n + 1) / 2, y = m - x;
    cout << 2 * min(x, y) + 1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
