/**
 * @file 108302H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 105

int n, m[maxn], s, t;
int a[maxn], b[maxn], c[maxn];
int64_t f[maxn][maxn][maxn];

int cil(int x, int y) { return x / y + (x % y > 0); }

bool chk(int p) {
    for (int i = 0; i <= n; i++)
        for (int x = 0; x <= t; x++)
            for (int y = 0; y <= t; y++) f[i][x][y] = -1;

    f[0][0][0] = 0;

    for (int i = 1; i <= n; i++)
        for (int x = 0; x <= t; x++)
            for (int y = 0; y <= t; y++) {
                if (!~f[i - 1][x][y]) continue;

                int ta = cil(a[i], m[i - 1]);
                if (x + ta <= t) f[i][x + ta][y] = max(f[i][x + ta][y], f[i - 1][x][y]);

                if (!p) continue;

                ta = cil(a[i] - c[i], m[i - 1]);
                int tb = cil(b[i], p), tt = max(x + ta, y + tb);
                if (tt <= t) f[i][tt][y + tb] = max(f[i][tt][y + tb], f[i - 1][x][y] + int64_t(tt - (x + ta)) * m[i - 1]);
            }

    for (int i = 0; i <= n; i++)
        for (int x = 0; x <= t; x++)
            for (int y = 0; y <= t; y++)
                if (~f[i][x][y] && f[i][x][y] + int64_t(t - x) * m[i] >= s) return true;

    return false;
}

void solve(void) {
    cin >> m[0] >> s >> t >> n;
    for (int i = 1, k; i <= n; i++) cin >> a[i] >> k >> b[i] >> c[i], m[i] = m[i - 1] + k;

    if (!chk(10000)) return cout << -1 << endl, void();
    int l = -1, r = 10000;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }
    cout << r << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
