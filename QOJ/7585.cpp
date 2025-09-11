/**
 * @file 7585.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t k;
    int m;
    cin >> k >> m;

    int64_t ans = INT64_MAX;
    for (int l = 1; l <= 800; l++) {
        int64_t n = k ^ l, x = n + l;
        int cnt = 0;
        for (int64_t i = n + 1; i < x; i++) cnt += (gcd(i, n) == 1);
        if (cnt == m - 1 && gcd(x, n) == 1) ans = min(ans, n);
    }

    cout << (ans == INT64_MAX ? -1 : ans) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
