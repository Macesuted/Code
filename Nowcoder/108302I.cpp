/**
 * @file 108302I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-29
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
    cout << ((n & 1) ? 2 * (n + (n + 1) / 2) : 2 * (n + 1 + n / 2)) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
