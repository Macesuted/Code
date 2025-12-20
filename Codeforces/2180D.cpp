/**
 * @file 2180D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
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

#define maxn 2000005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    if (n == 1) return cout << 0 << endl, void();

    int l = 0, r = a[2] - a[1], ans = 0;
    for (int i = 2; i <= n; i++) {
        int d = a[i] - a[i - 1];
        int nl = d - r, nr = d - l;
        if (i < n) nr = min(nr, a[i + 1] - a[i]);
        if (nl < nr)
            ans++;
        else {
            nl = 0, nr = d;
            if (i < n) nr = min(nr, a[i + 1] - a[i]);
        }
        l = nl, r = nr;
    }

    cout << ans << endl;

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
