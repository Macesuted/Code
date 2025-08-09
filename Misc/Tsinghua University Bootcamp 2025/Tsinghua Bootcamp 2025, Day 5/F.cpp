/**
 * @file F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int cnt = 0;

int64_t query(int l1, int r1, int l2, int r2) {
    cout << "? " << l1 << ' ' << l2 << ' ' << r1 << ' ' << r2 << endl;
    int64_t ret;
    cin >> ret;
    return ret;
}

void solve(void) {
    int lp1, lp2, rp1, rp2;

    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (query(1, 1e9, 1, mid) >= int64_t(1e9) * mid + 2 ? r : l) = mid;
    }

    rp2 = r;

    l = 0;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (query(1, 1e9, 1, mid) >= int64_t(1e9) * mid + 1 ? r : l) = mid;
    }

    rp1 = r;

    l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (query(1, mid, 1, 1e9) >= int64_t(1e9) * mid + 2 ? r : l) = mid;
    }

    lp2 = r;

    l = 0;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (query(1, mid, 1, 1e9) >= int64_t(1e9) * mid + 1 ? r : l) = mid;
    }

    lp1 = r;

    if (query(lp1, lp1, rp1, rp1) == 1)
        cout << "! " << lp1 << ' ' << rp2 << ' ' << lp2 << ' ' << rp1 << endl;
    else
        cout << "! " << lp1 << ' ' << rp1 << ' ' << lp2 << ' ' << rp2 << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}