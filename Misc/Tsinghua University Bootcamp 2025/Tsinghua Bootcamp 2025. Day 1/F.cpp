/**
 * @file F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t n, m, s;
    cin >> n >> m >> s;

    if (s == n * m) return cout << 0 << endl, void();
    if (s % n == 0 || s % m == 0) return cout << 1 << endl, void();

    int64_t rest = n * m - s;
    for (int64_t x = 1; x <= n; x++) {
        if (s % x == 0 && 1 <= s / x && s / x <= m) return cout << 2 << endl, void();
        if (rest % x == 0 && 1 <= rest / x && rest / x <= m) return cout << 2 << endl, void();
    }

    for (int64_t x = 1; x < n; x++) {
        int64_t k = 2 * x - n, b = n * m - x * m;

        if (k == 0) {
            if (s == b) return cout << 2 << endl, void();
            continue;
        }

        if ((s - b) % k) continue;
        int64_t y = (s - b) / k;
        if (1 <= y && y <= m) return cout << 2 << endl, void();
    }

    return cout << 3 << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
