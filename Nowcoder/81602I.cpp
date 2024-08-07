/**
 * @file 81602I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int m, k, h;
    cin >> m >> k >> h;
    if (k == m) return cout << min(h, m) << endl, void();
    int l = 0, r = h;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1, tot = mid;
        if (mid >= m) tot += ((mid - m) / (m - k) + 1) * k;
        (tot >= h ? r : l) = mid;
    }
    cout << r << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}