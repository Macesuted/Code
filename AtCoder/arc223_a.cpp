/**
 * @file arc223_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 65

int64_t w[maxn], v[maxn];

void solve(void) {
    int n;
    int64_t W;
    cin >> n >> W;

    int64_t sumw = 0, sumv = 0, ans = 0, cur = 0;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i], sumw += w[i], sumv += v[i];

    if (sumw <= W) return cout << sumv << endl, void();

    for (int i = n; i; i--) {
        if (sumw <= W) return cout << max(ans, cur + sumv) << endl, void();
        sumw -= w[i], sumv -= v[i];
        if (w[i] <= W) ans = max(ans, cur + sumv), cur += v[i], W -= w[i];
    }

    ans = max(ans, cur);

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
