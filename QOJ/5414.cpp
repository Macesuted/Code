/**
 * @file 5414.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2005

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;

    int xl = 1, xr = n, yl = 1, yr = m, dx = 0, dy = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == 'U') xl--, xr--, dx--;
        if (s[i] == 'D') xl++, xr++, dx++;
        if (s[i] == 'L') yl--, yr--, dy--;
        if (s[i] == 'R') yl++, yr++, dy++;
        if (xl < 1) xl = 1;
        if (xr > n) xr = n;
        if (yl < 1) yl = 1;
        if (yr > m) yr = m;
    }
    xl -= dx, xr -= dx, yl -= dy, yr -= dy;

    if (xl > xr || yl > yr) return cout << (k == 0 ? n * m : 0) << endl, void();

    int x0 = n + 5, y0 = m + 5;
    int x = x0, y = y0;
    vector<vector<int>> f(x0 + n + 5, vector<int>(y0 + m + 5, 0));
    f[x0][y0] = 1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == 'U') x++;
        if (s[i] == 'D') x--;
        if (s[i] == 'L') y++;
        if (s[i] == 'R') y--;
        f[x][y] = 1;
    }

    for (int i = 0; i < (int)f.size(); i++)
        for (int j = 1; j < (int)f[0].size(); j++) f[i][j] += f[i][j - 1];
    for (int i = 1; i < (int)f.size(); i++)
        for (int j = 0; j < (int)f[0].size(); j++) f[i][j] += f[i - 1][j];

    auto sum = [&](int xl, int xr, int yl, int yr) -> int {
        return f[xr][yr] - f[xl - 1][yr] - f[xr][yl - 1] + f[xl - 1][yl - 1];
    };

    k = (xr - xl + 1) * (yr - yl + 1) - k;

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans += (sum(xl - i + x0, xr - i + x0, yl - j + y0, yr - j + y0) == k);

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
