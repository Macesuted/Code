/**
 * @file 11521.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

int64_t a[maxn], f[maxn], sl[maxn], sr[maxn];
uint64_t fsum[maxn], slsum[maxn];

uint64_t solve(int l, int r) {
    if (l == r) return a[l];
    int mid = (l + r) >> 1;
    uint64_t ans = solve(l, mid) + solve(mid + 1, r);

    int64_t sum = 0, maxv = a[mid];
    for (int i = mid; i >= l; i--) f[i] = maxv = max(maxv, sum = max(sum, (int64_t)0) + a[i]);
    sum = 0, maxv = a[mid + 1];
    for (int i = mid + 1; i <= r; i++) f[i] = maxv = max(maxv, sum = max(sum, (int64_t)0) + a[i]);

    sum = 0, maxv = a[mid];
    for (int i = mid; i >= l; i--) sr[i] = maxv = max(maxv, sum += a[i]);
    sum = 0, maxv = a[mid + 1];
    for (int i = mid + 1; i <= r; i++) sl[i] = maxv = max(maxv, sum += a[i]);

    slsum[mid] = fsum[mid] = 0;
    for (int i = mid + 1; i <= r; i++) slsum[i] = slsum[i - 1] + sl[i], fsum[i] = fsum[i - 1] + f[i];

    for (int i = mid; i >= l; i--) {
        int p = lower_bound(f + mid + 1, f + r + 1, f[i]) - f;

        auto calc = [&](int xl, int xr, int64_t v) -> uint64_t {
            int c = lower_bound(sl + xl, sl + xr + 1, v - sr[i]) - sl;
            uint64_t ret = 0;
            if (xl <= c - 1) ret += (uint64_t)v * ((c - 1) - xl + 1);
            if (c <= xr) ret += (uint64_t)sr[i] * (xr - c + 1) + slsum[xr] - slsum[c - 1];
            return ret;
        };

        if (mid + 1 <= p - 1) ans += calc(mid + 1, p - 1, f[i]);
        if (p <= r) {
            int xl = p - 1, xr = r + 1;
            while (xl + 1 < xr) {
                int mid = (xl + xr) >> 1;
                (sr[i] + sl[mid] >= f[mid] ? xl : xr) = mid;
            }
            if (p <= xl) ans += (uint64_t)sr[i] * (xl - p + 1) + slsum[xl] - slsum[p - 1];
            if (xr <= r) ans += fsum[r] - fsum[xl];
        }
    }

    return ans;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << solve(1, n) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
