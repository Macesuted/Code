/**
 * @file 15899.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int64_t a[maxn], f[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    f[1] = a[1], f[n] = 0;
    for (int i = 2; i < n; i++) f[i] = a[i] - f[i - 1];

    if (n & 1) {
        int64_t x = (a[n] - f[n - 1]) / 2;
        for (int i = 1; i < n; i++) f[i] += (i & 1) ? -x : +x;
        f[n] += x;

        int64_t maxv = INT64_MIN, sum = 0;
        for (int i = 1; i <= n; i++) maxv = max(maxv, f[i]), sum += f[i];
        cout << max(maxv, sum / (n - 1) + (sum % (n - 1) > 0)) << endl;

        return;
    }

    int64_t maxu = INT64_MIN, minu = INT64_MAX, maxd = INT64_MIN, mind = INT64_MAX, sum = 0;
    for (int i = 1; i <= n; i += 2) maxd = max(maxd, f[i]), mind = min(mind, f[i]), sum += f[i];
    for (int i = 2; i <= n; i += 2) maxu = max(maxu, f[i]), minu = min(minu, f[i]), sum += f[i];

    int64_t ans = INT64_MAX;
    int64_t X = max(min((maxd - maxu) / 2, mind), -minu);
    for (int64_t x = X - 10; x <= X + 10; x++) {
        if (mind - x < 0 || minu + x < 0) continue;
        int64_t maxv = max(maxd - x, maxu + x);
        ans = min(ans, max(maxv, sum / (n - 1) + (sum % (n - 1) > 0)));
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
