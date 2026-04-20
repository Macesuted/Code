/**
 * @file 2219A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-13
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

void solve(void) {
    int p, q;
    cin >> p >> q;

    int sum = p + 2 * q;
    for (int n = 1; n * n <= sum; n++) {
        if ((sum - n) % (2 * n + 1)) continue;
        int m = (sum - n) / (2 * n + 1);

        if (p >= abs(n - m)) return cout << n << ' ' << m << endl, void();
    }

    cout << -1 << endl;

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
