/**
 * @file 1621B.cpp
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
    int n;
    cin >> n;
    int l = 1e9, r = 0, L = 1e9, R = 1e9, Lo = 1e9, Ll = 0;
    for (int i = 1; i <= n; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if (x < l) L = c, l = x;
        if (x == l) L = min(L, c);
        if (y > r) R = c, r = y;
        if (y == r) R = min(R, c);
        if (y - x + 1 > Ll) Ll = y - x + 1, Lo = c;
        if (y - x + 1 == Ll) Lo = min(Lo, c);
        int cost = L + R;
        if (Ll == r - l + 1) cost = min(cost, Lo);
        cout << cost << endl;
    }
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
