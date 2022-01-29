/**
 * @file 1623A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-29
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
    int n, m, rb, cb, rd, cd;
    cin >> n >> m >> rb >> cb >> rd >> cd;
    int ans = 0x3f3f3f3f;
    if (rb <= rd)
        ans = min(ans, rd - rb);
    else
        ans = min(ans, n + (n - rd) - rb);
    if (cb <= cd)
        ans = min(ans, cd - cb);
    else
        ans = min(ans, m + (m - cd) - cb);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
