/**
 * @file 14608.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int a[20];
int64_t pw10[20];
int f[20][3][10005], g[100005];

void solve(void) {
    int64_t m;
    int n;
    cin >> m >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int c = 0; c < 9; c++) {
        for (int i = 0; i <= 19; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 10000; k++) f[i][j][k] = -1;

        auto cnt = [&](int b) -> bool { return b == c || (c == 6 && b == 9); };

        int ans = 0;

        for (int i = 0; i <= 18 && pw10[i] <= m; i++) ans += cnt(m / pw10[i] % 10);

        if (c == 0) ans = max(ans, 1);

        f[0][1][0] = 0;
        for (int i = 0; i <= 18 && pw10[i] <= m; i++) {
            int mb = m / pw10[i] % 10;
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 10000; k++) g[k] = f[i][j][k];
                for (int k = 10000; k < 100000; k++) g[k] = -1;

                for (int t = 1; t <= n; t++)
                    for (int k = 0; k + a[t] < 100000; k++) g[k + a[t]] = max(g[k + a[t]], g[k]);

                for (int k = 1; k < 10; k++) {
                    if (!~g[k]) continue;
                    if (k < m / pw10[i] || (k == m / pw10[i] && j <= 1)) ans = max(ans, g[k] + cnt(k));
                }

                for (int k = 0; k < 100000; k++) {
                    if (!~g[k]) continue;
                    int b = k % 10, nk = k / 10, w = g[k] + cnt(b);
                    if (b < mb)
                        f[i + 1][0][nk] = max(f[i + 1][0][nk], w);
                    else if (b == mb)
                        f[i + 1][j][nk] = max(f[i + 1][j][nk], w);
                    else
                        f[i + 1][2][nk] = max(f[i + 1][2][nk], w);
                }
            }
        }

        if (ans) cout << c << ' ' << ans << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    pw10[0] = 1;
    for (int i = 1; i <= 18; i++) pw10[i] = pw10[i - 1] * 10;

    int _ = 1;
    while (_--) solve();

    return 0;
}