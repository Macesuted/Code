/**
 * @file 1629B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

void solve(void) {
    int l, r, k;
    cin >> l >> r >> k;
    if (l == 1 && r == 1) return cout << "NO" << endl, void();
    if (l == r) return cout << "YES" << endl, void();
    int cnt = r / 2 - (l - 1) / 2;
    cout << (r - l + 1 - cnt <= k ? "YES" : "NO") << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
