/**
 * @file 14407.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int a, b, c;
    cin >> a >> b >> c;

    int ans = a / 3 + b / 3 + c / 3;

    if (a % 3 == 2 && b % 3 == 2 && c % 3 == 2) return cout << ans + 2 << endl, void();

    if (a % 3 + b % 3 + c % 3 >= 3) {
        if (max(b % 3, c % 3) >= 2) return cout << ans + 1 << endl, void();
        if (a % 3 >= 1 && b % 3 >= 1 && (b / 3 >= 1 || c / 3 >= 2)) return cout << ans + 1 << endl, void();
        if (a % 3 >= 1 && c % 3 >= 1 && (b / 3 >= 2 || c / 3 >= 1)) return cout << ans + 1 << endl, void();
        if (a % 3 >= 2 && b % 3 >= 1 && c % 3 >= 1 && (b / 3 >= 1 || c / 3 >= 1)) return cout << ans + 1 << endl, void();
    }

    return cout << ans << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
