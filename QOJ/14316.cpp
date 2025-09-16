/**
 * @file 14316.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int S, f[8];
    cin >> S;
    for (int i = 1; i <= 7; i++) cin >> f[i];

    auto chk = [&](int lim) {
        int of[8], v[3] = {f[1], f[2], f[4]}, o3 = 0, o7 = 0;
        for (int i = 1; i <= 7; i++) of[i] = f[i];

        if (v[0] < lim) {
            int t = min(lim - v[0], of[3]);
            v[0] += t, of[3] -= t, o3 += t;
        }
        if (v[0] < lim) {
            int t = min(lim - v[0], of[5]);
            v[0] += t, of[5] -= t;
        }
        if (v[0] < lim) {
            int t = min(lim - v[0], of[7]);
            v[0] += t, of[7] -= t, o7 += t;
        }
        if (v[0] < lim) return false;

        if (v[1] < lim) {
            int t = min(lim - v[1], of[3]);
            v[1] += t, of[3] -= t;
        }
        if (v[1] < lim) {
            int t = min(lim - v[1], of[6]);
            v[1] += t, of[6] -= t;
        }
        if (v[1] < lim) {
            int t = min(lim - v[1], of[7]);
            v[1] += t, of[7] -= t;
        }
        if (v[1] < lim) {
            int t = min({lim - v[1], o3, of[5]});
            v[1] += t, of[5] -= t;
        }
        if (v[1] < lim) {
            int t = min({lim - v[1], o7, of[7]});
            v[1] += t, of[7] -= t;
        }
        if (v[1] < lim) return false;

        if (v[2] < lim) {
            int t = min(lim - v[2], of[5]);
            v[2] += t, of[5] -= t;
        }
        if (v[2] < lim) {
            int t = min(lim - v[2], of[6]);
            v[2] += t, of[6] -= t;
        }
        if (v[2] < lim) {
            int t = min(lim - v[2], of[7]);
            v[2] += t, of[7] -= t;
        }
        if (v[2] < lim) return false;

        return true;
    };

    int l = 0, r = S;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? l : r) = mid;
    }
    cout << l << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}