/**
 * @file 875.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

int a[maxn], b[maxn], d[maxn], p[maxn], sa[maxn], sb[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> a[i], sa[i] = sa[i - 1] + a[i];
    for (int i = 1; i <= k; i++) cin >> b[i], sb[i] = sb[i - 1] + b[i];
    d[0] = 0;
    for (int i = 1; i <= k; i++) d[0] = max(d[0], sa[i] - sb[i]);
    int ans = d[0];
    for (int i = 1; i <= k; i++) d[i] = sb[i] - sa[i] + d[0], ans += d[i], p[i] = a[i];
    bool chk = true;
    while (chk) {
        chk = false, p[0] = -1, p[k + 1] = n + 2;
        for (int i = 0; i <= k; i++) {
            int x = (p[i + 1] - p[i] - 2) / 2;
            if (i == 0) x = p[i + 1] - 2;
            if (i == k) x = n - p[i] - 1;
            x = min(d[i], x);
            if (x <= 0) continue;
            d[i] -= x, p[i] += x, p[i + 1] -= x, chk = true;
        }
    }
    for (int i = 0; i <= k; i++)
        if (d[i]) return cout << "impossible" << endl, void();
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}