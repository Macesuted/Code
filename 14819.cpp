/**
 * @file 14819.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define mod 1'000'000'007

int64_t f[maxn], g[maxn], h[maxn], a[maxn], mul[maxn], sum[maxn];

void solve(void) {
    int n, x;
    cin >> n >> x;
    mul[0] = sum[0] = 1;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = (sum[i - 1] + (mul[i] = mul[i - 1] * a[i] % mod)) % mod;

    auto add = [&](int64_t &x, int64_t y) -> int64_t { return x = (x + y) % mod; };

    int64_t ans = mul[n];
    for (int i = 1; i <= n; i++) f[i] = g[i] = h[i] = 0;
    f[n + 1] = 1, g[n + 1] = h[n + 1] = 0;
    for (int i = n + 1; i >= 1; i--) {
        if (i > 1 && a[i] > 1) add(h[i - 1], h[i]);
        if (i > 2 && a[i] == 1) add(h[i - 2], h[i]);

        if (a[i] > 1) add(f[i], h[i]), add(g[i], h[i] * (a[i] - 2));
        if (i > 2 && a[i - 2] == a[i]) add(f[i - 2], h[i]);
        if (i > 1) add(f[i - 1], h[i]), add(g[i - 1], h[i] * (a[i - 1] - 1));

        if (i > 1) add(f[i - 1], f[i]), add(g[i - 1], f[i] * (a[i - 1] - 1));
        if (i > 2) add(h[i - 2], f[i]);

        if (i > 1) add(f[i - 1], g[i]), add(g[i - 1], g[i] * (a[i - 1] - 1));
        if (i > 1) add(h[i - 1], g[i]);

        if (i > 2) add(ans, (sum[i - 3] + mul[i - 3] * (a[i - 2] - 1)) % mod * f[i]);
        if (i > 1) add(ans, (sum[i - 2] + mul[i - 2] * (a[i - 1] - 1)) % mod * g[i]);
        if (i > 1 && a[i] > 1) add(ans, (sum[i - 2] + mul[i - 2] * (a[i - 1] - 1)) % mod * h[i]);
        if (i > 2 && a[i] == 1) add(ans, (sum[i - 3] + mul[i - 3] * (a[i - 2] - 1)) % mod * h[i]);
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