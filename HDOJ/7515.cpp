/**
 * @file 7515.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    int64_t x, y;
    cin >> x >> y;
    if (x % y == 0) return cout << y << ' ' << x / y << endl, void();
    cout << y << ' ' << 2 * x / gcd(2 * x, y) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}