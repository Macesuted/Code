/**
 * @file 5420.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

using pii = pair<int, int>;

int a[maxn], pre[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    pre[0] = 1;
    for (int i = 1; i <= n; i++)
        if ((pre[i] = pre[i - 1] + (a[i] >= 0 ? +1 : -1)) <= 0) return cout << -1 << endl, void();

    int cnt = pre[n], sum = 1 + n - (n + 1 - pre[n]) / 2, low = pre[n];
    pii ans = {sum, cnt};
    for (int i = n; i; i--) {
        low = min(low, pre[i]);
        if (a[i] == 0) cnt -= 2, sum--, low -= 2;
        if (low <= 0) break;
        if ((int64_t)ans.first * cnt < (int64_t)sum * ans.second) ans = {sum, cnt};
    }

    int64_t g = gcd(ans.first, ans.second);
    cout << ans.first / g << ' ' << ans.second / g << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
