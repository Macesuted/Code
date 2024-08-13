/**
 * @file 81604I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

__int128 sqrt128(__int128 v) {
    __int128 l = 0, r = pow(10, 16);
    while (l + 1 < r) {
        __int128 mid = l + (r - l) / 2;
        (mid * mid <= v ? l : r) = mid;
    }
    return l;
}

void print(__int128 ans) {
    if (!ans) return cout << 0, void();
    stack<char> S;
    while (ans) S.push(ans % 10 + '0'), ans /= 10;
    while (!S.empty()) cout << S.top(), S.pop();
    return;
}

void solve(void) {
    int n;
    cin >> n, n >>= 1;
    string L, R;
    cin >> L >> R;
    __int128 lv = 0, rv = 0;
    for (int i = 0; i < n; i++) lv = lv * 10 + L[i] - '0', rv = rv * 10 + R[i] - '0';
    __int128 sl = sqrt128(lv), sr = sqrt128(rv);
    if (lv == rv) {
        if (sl * sl != lv) return cout << 0 << endl, void();
        lv = rv = 0;
        for (int i = n; i < 2 * n; i++) lv = lv * 10 + L[i] - '0', rv = rv * 10 + R[i] - '0';
        print(sqrt128(rv) - (lv ? sqrt128(lv - 1) : -1)), cout << endl;
        return;
    }
    __int128 vd = sr - sl, vl = 0, vr = 0;
    if (sl * sl == lv) vl = 1;
    if (sr * sr == rv) vd--, vr = 1;
    __int128 ans = 0, full = 1;
    lv = rv = 0;
    for (int i = n; i < 2 * n; i++) lv = lv * 10 + L[i] - '0', rv = rv * 10 + R[i] - '0', full *= 10;
    full = sqrt128(full - 1);
    if (vl) ans += (lv ? full - sqrt128(lv - 1) : full + 1);
    if (vr) ans += sqrt128(rv) + 1;
    ans += vd * (full + 1);
    print(ans), cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}