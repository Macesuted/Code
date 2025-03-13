/**
 * @file 10117.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int cnt0[10], cnt1[10];

void solve(void) {
    int64_t n;
    cin >> n;

    memset(cnt0, 0, sizeof(cnt0));

    int64_t d = 1;
    while (d <= n / 10) d *= 10;

    for (int64_t i = d; i; i /= 10) cnt0[n / i % 10]++;

    int ans = 0;
    for (int i = 2; n / i >= d; i++) {
        if (n % i) continue;
        memset(cnt1, 0, sizeof(cnt1));
        for (int64_t j = d; j; j /= 10) cnt1[n / i / j % 10]++;
        bool chk = true;
        for (int j = 0; j < 10; j++) chk &= (cnt0[j] == cnt1[j]);
        ans += chk;
    }

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
