/**
 * @file 104077E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int64_t pow3[39];

int64_t solve(int dep, int64_t l, int64_t r, int64_t ql, int64_t qr, bool pre = false) {
    if (ql <= l && r <= qr) return (dep + 1) * 3;
    int64_t m1 = r - 2 * pow3[dep], m2 = r - pow3[dep], ans = 0;
    if (ql <= m1 && qr >= l) ans = max(ans, solve(dep - 1, l, m1, ql, qr, pre) + pre);
    if (ql <= m2 && qr >= m1 + 1) ans = max(ans, solve(dep - 1, m1 + 1, m2, ql, qr, true) + 2);
    if (ql <= r && qr >= m2 + 1) ans = max(ans, solve(dep - 1, m2 + 1, r, ql, qr, true) + 3);
    return ans;
}

void solve(void) {
    int64_t l, r;
    cin >> l >> r;
    cout << solve(37, 0, pow3[38] - 1, l, r) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    pow3[0] = 1;
    for (int i = 1; i < 39; i++) pow3[i] = pow3[i - 1] * 3;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}