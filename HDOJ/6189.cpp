/**
 * @file 6189.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

int64_t qpow(int64_t a, int64_t x, int64_t mod) {
    int64_t ans = 1 & (mod - 1);
    while (x) {
        if (x & 1) ans = (ans * a) & (mod - 1);
        a = (a * a) & (mod - 1), x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n, a;
    while (cin >> n >> a) {
        if (a & 1) {
            cout << 1 << endl;
            continue;
        }

        int m = 1 << n, ans = 0;
        for (int b = 1; b <= n; b++) ans += (qpow(a, b, m) == qpow(b, a, m));
        for (int t = 1; t <= n; t++) {
            if ((int64_t)t * a < n) continue;
            ans += (((m >> t) + 1) >> 1) - (((n >> t) + 1) >> 1);
        }

        cout << ans << endl;
    }
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