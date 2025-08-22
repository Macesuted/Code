/**
 * @file L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 505

int a[maxn], l[maxn], r[maxn], xl[maxn], xr[maxn];
double f[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> l[i];
    for (int i = 1; i <= n; i++) cin >> r[i];

    for (int i = 1; i <= n; i++) {
        int pl = i, pr = i, nl = i - l[i], nr = i + r[i];
        while (pl != nl || pr != nr) {
            int tl = nl, tr = nr;
            for (int i = nl; i < pl; i++) tl = min(tl, i - l[i]), tr = max(tr, i + r[i]);
            for (int i = nr; i > pr; i--) tl = min(tl, i - l[i]), tr = max(tr, i + r[i]);
            pl = nl, pr = nr;
            nl = tl, nr = tr;
        }
        xl[i] = pl, xr[i] = pr;
    }

    for (int i = 1; i <= n + 1; i++) f[i][i - 1] = 1;

    for (int len = 1; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++) {
            f[l][r] = 0;
            for (int p = l; p <= r; p++) {
                if (a[p] == 1 && !(l <= xl[p] && xr[p] <= r)) continue;
                if (a[p] == 2 && l <= xl[p] && xr[p] <= r) continue;
                f[l][r] += f[l][p - 1] * f[p + 1][r] / (r - l + 1);
            }
        }

    cout << fixed << setprecision(15) << f[1][n] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
