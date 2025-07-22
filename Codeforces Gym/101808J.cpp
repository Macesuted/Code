/**
 * @file 101808J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

int L[2], R[2], P[2], D[2];

void solve(void) {
    for (int t = 0; t < 2; t++) cin >> L[t] >> R[t] >> P[t] >> D[t];
    int tim, ans = 0;
    cin >> tim;
    for (int i = 1; i <= tim; i++) {
        for (int t = 0; t < 2; t++) {
            if (P[t] == L[t]) D[t] = 1;
            if (P[t] == R[t]) D[t] = 0;
            P[t] += D[t] ? +1 : -1;
        }
        ans += (P[0] == P[1]);
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