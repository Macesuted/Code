/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

using pii = pair<int, int>;

int ask(int x, int y) {
    cout << "ask " << x << ' ' << y << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve(int c1, int x1, int y1, int c2, int x2, int y2) {
    if (x1 > x2) swap(x1, x2), swap(y1, y2), swap(c1, c2);

    auto gen = [&](int d) -> pii {
        int x = x1 + d, y;
        if (y1 < y2) {
            y = y1 + d;
            if (x > x2) y += x - x2, x = x2;
            if (y > y2) x += y - y2, y = y2;
        }
        if (y2 <= y1) {
            y = y1 - d;
            if (x > x2) y -= x - x2, x = x2;
            if (y < y2) x += y2 - y, y = y2;
        }
        return {x, y};
    };

    int mn = abs(x1 - x2), mx = abs(y1 - y2);
    if (mn > mx) swap(mn, mx);
    int l = 0, r = mn + (mx - mn) / 2;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        auto [x, y] = gen(mid);
        (ask(x, y) == c1 ? l : r) = mid;
    }

    auto [xl, yl] = gen(l);
    auto [xr, yr] = gen(r);

    if (xr - xl == 0) {
        int xc = xl, yc = (yl + yr) / 2;
        ask(xc, yc);
        ask(xc + (xc > 1 ? -1 : +1), yc);
    }
    if (xr - xl == 1) ask(xl + 1, yl);
    if (xr - xl == 2) {
        int xc = (xl + xr) / 2, yc = yl;
        ask(xc, yc);
        ask(xc, yc + (yc > 1 ? -1 : +1));
    }

    cout << "done" << endl;

    return;
}

void solve(void) {
    int n, m, x[3], y[3];
    cin >> n >> m;
    for (int t = 0; t < 3; t++) cin >> x[t] >> y[t];

    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
            if (a != b && (x[a] + y[a]) % 2 == (x[b] + y[b]) % 2) return solve(a + 1, x[a], y[a], b + 1, x[b], y[b]);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}