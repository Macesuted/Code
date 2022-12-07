/**
 * @file 2734.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-07
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

void solve(void) {
    int64_t n, m, pre = 0, minp = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        string a;
        int64_t k, s = 0, mp = pre;
        cin >> a >> k;
        for (auto j : a) mp = min(mp, pre + (s += (j == 'M' ? +1 : -1)));
        minp = min({minp, mp, mp + s * (k - 1)}), pre += s * k;
    }
    if (pre > 0) return cout << -1 << endl, void();
    cout << max((int64_t)0, (pre - 1) - minp) << endl;
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