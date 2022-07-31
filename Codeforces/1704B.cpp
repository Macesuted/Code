/**
 * @file 1704B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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
    int n, x, ans = 0, lef = INT_MAX, rig = INT_MIN;
    cin >> n >> x;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        lef = min(lef, a), rig = max(rig, a);
        if (rig - lef > 2 * x) lef = rig = a, ans++;
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