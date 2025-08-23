/**
 * @file 108307D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t n;
    cin >> n;
    cout << ((n - 4) % 6 == 0 ? 2 : 0) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}