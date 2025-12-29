/**
 * @file 2178E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int lg2(int64_t x) {
    int cnt = 0;
    while (!(x & 1)) x >>= 1, cnt++;
    return cnt;
}

int64_t query(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    int64_t ret;
    cin >> ret;
    return ret;
}

int solve(int l, int r, int k) {
    if (l == r) return k;

    int64_t tar = (int64_t)1 << (k - 1);

    int xl = l, xr = r;
    while (xl + 1 < xr) {
        int mid = (xl + xr) >> 1;
        (query(l, mid) <= tar ? xl : xr) = mid;
    }

    return xr - l <= r - xl ? solve(l, xl, k - 1) : solve(xr, r, k - 1);
}

void solve(void) {
    int n;
    cin >> n;

    int k = solve(1, n, lg2(query(1, n)));

    cout << "! " << ((int64_t)1 << k) << endl;

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
