/**
 * @file 14547.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 2, vector<int>(m + 2, 0));

    auto add = [&](int xl, int xr, int yl, int yr) -> void {
        a[xl][yl]++;
        a[xl][yr + 1]--;
        a[xr + 1][yl]--;
        a[xr + 1][yr + 1]++;
        return;
    };

    for (int x = 0; x <= min(n, m); x++)
        for (int y = 1; x + y <= min(n, m); y++) {
            add(0, n - x - y, x, m - y);
            add(y, n - x, 0, m - x - y);
            add(x + y, n, y, m - x);
            add(x, n - y, x + y, m);
        }

    for (int i = 0; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] += a[i][j - 1];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) a[i][j] += a[i - 1][j];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) cout << a[i][j] << ' ';
        cout << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
