/**
 * @file 5471.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int query(int64_t v) {
    cout << "query " << v << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve(void) {
    int s = query(0);
    int64_t ans = 0, pw10 = 1;
    for (int t = 0; t < 18; t++, pw10 *= 10) {
        int l = 1, r = 9, x = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (query(m * pw10) == s + m)
                x = m, l = m + 1;
            else
                r = m - 1;
        }
        ans += (9 - x) * pw10;
    }

    cout << "answer " << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}