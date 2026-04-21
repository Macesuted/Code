/**
 * @file 2225D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-21
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
    int64_t n, x;
    cin >> n >> x;

    __int128_t l[2] = {((x - 1) >> 2) + 2 - (((x - 1) & 3) < 3), ((x - 1) >> 2) + 1 - (((x - 1) & 3) < 1)},
               r[2] = {((n >> 2) + 2 - ((n & 3) < 3)), (n >> 2) + 1 - ((n & 3) < 1)};
    r[0] -= l[0], r[1] -= l[1];

    cout << int64_t((l[0] * r[0] + l[1] * r[1]) % 998244353) << endl;

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
