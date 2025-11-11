/**
 * @file 14825.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 15

int X[maxn], Y[maxn];

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) cin >> X[i] >> Y[i];
    for (int S = 0; S < (1 << k); S++)
        cout << [&](void) -> int {
            int xl = 1, xr = n, pl = 1, pr = n, y = 1, d = 0;
            for (int l = 0, r; l < k; l = r + 1) {
                r = l;
                while (r + 1 < k && Y[r + 1] == Y[l]) r++;

                int ql = 1, qr = n;
                for (int i = l; i <= r; i++)
                    if (S >> i & 1)
                        ql = max(ql, X[i] + 1);
                    else
                        qr = min(qr, X[i] - 1);
                if (ql > qr) return -1;

                if (Y[l] == 1) {
                    l = ql, r = qr;
                    continue;
                }
                if (Y[l] == y + 1 && (pr < ql || qr < pl)) return -1;
                if (xr < ql) d += ql - xr, xl = xr = ql;
                if (xl > qr) d += xl - qr, xl = xr = qr;
                xl = max(xl, ql), xr = min(xr, qr);
                d += Y[l] - y, y = Y[l];
                pl = ql, pr = qr;
            }
            return d + (m - y);
        }() << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}