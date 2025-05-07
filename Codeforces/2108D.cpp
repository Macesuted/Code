/**
 * @file 2108D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int query(int p) {
    cout << "? " << p << endl;
    int x;
    cin >> x;
    return x;
}

void solve(void) {
    int n, k;
    cin >> n >> k;

    if (n == 2 * k) return cout << "! " << k << ' ' << k << endl, void();

    int xl = k, xr = n - k + 1;
    for (int i = 1; i <= k && xl + 1 < xr; i++) {
        int l = xl / k, r = xr / k - 1;
        while (i + l * k > xl) l--;
        while (i + r * k < xr) r++;

        int v = query(i + l * k);
        if (query(i + r * k) == v) continue;

        while (l + 1 < r) {
            int m = (l + r) >> 1;
            (query(i + m * k) == v ? l : r) = m;
        }
        xl = max(xl, i + l * k), xr = min(xr, i + r * k);
    }

    if (xl + 1 != xr) return cout << "! -1" << endl, void();

    cout << "! " << xl << ' ' << n - xr + 1 << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}