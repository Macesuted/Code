/**
 * @file 108330F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n, a, b;
    cin >> n >> a >> b;
    int t = n % (a + b), ans = 0;
    if (1 <= t && t <= a) ans = t, n -= t;
    if (n == 0) return cout << "Sayonara" << endl, void();
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
