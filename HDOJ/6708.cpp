/**
 * @file 6708.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using namespace std;

#define maxn 1050

bool s[maxn][maxn];

void solve(int xl, int xr, int yl, int yr, bool rev = false) {
    if (xl == xr && yl == yr) return s[xl][yl] = rev, void();
    int xm = (xl + xr) / 2, ym = (yl + yr) / 2;
    solve(xl, xm, yl, ym, rev), solve(xl, xm, ym + 1, yr, rev);
    solve(xm + 1, xr, yl, ym, !rev), solve(xm + 1, xr, ym + 1, yr, rev);
    return;
}

int main() {
    int _;
    cin >> _;
    while (_--) {
        int k;
        cin >> k;
        solve(1, 1 << k, 1, 1 << k);
        for (int i = 1; i <= (1 << k); i++) {
            for (int j = 1; j <= (1 << k); j++) cout << "CP"[s[i][j]];
            cout << endl;
        }
    }
    return 0;
}