/**
 * @file 108302E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn], ppcnt[maxn];

void solve(void) {
    int64_t n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i], ppcnt[i] = 0;

    int64_t ans = 0;
    for (int t = 0; t < 30; t++) {
        int64_t cnt[2][2] = {{0, 0}, {0, 0}};
        for (int i = 1; i <= n; i++) cnt[a[i] >> t & 1][ppcnt[i] & 1]++, ppcnt[i] += a[i] >> t & 1;
        ans += (cnt[0][0] * cnt[1][0] + cnt[0][1] * cnt[1][1]) << t;
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
