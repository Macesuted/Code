/**
 * @file 10480.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 4005

const int dw[5][2] = {{0, 0}, {0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

int mp[256], way[maxn], a[maxn][maxn];

int cx, cy;
int query(int w) {
    cout << ".>v<^G"[w] << endl;
    cx += dw[w][0], cy += dw[w][1];

    char c;
    cin >> c;
    if (mp[c] == 5) exit(0);
    return a[cx][cy] = mp[c];
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i <= 2 * n + 1; i++)
        for (int j = 1; j <= 2 * n + 1; j++) a[i][j] = -1;

    auto get = [&](int x, int y) -> int {
        if (a[x][y] != -1) return a[x][y];
        while (cy < y) query(1);
        while (cx < x) query(2);
        while (cy > y) query(3);
        while (cx > x) query(4);
        return a[x][y];
    };

    int xl = 1, xr = 2 * n + 1, yl = 1, yr = 2 * n + 1;
    cx = cy = n + 1, a[cx][cy] = 4;

    for (int x = n; x >= 1; x--) get(x, n + 1);
    for (int x = 1; x <= 2 * n + 1; x++) get(x, n + 2);
    for (int x = 2 * n + 1; x > n; x--) get(x, n + 1);

    auto chk = [&](int xl, int xr, int yl, int yr) -> bool {
        int in = (xl <= n + 1 && n + 1 <= xr && yl <= n + 1 && n + 1 <= yr);
        if (xl != 1)
            for (int y = yl; y <= yr; y++) {
                if (a[xl - 1][y] == 2) in++;
                if (a[xl][y] == 4) in--;
            }
        if (xr != 2 * n + 1)
            for (int y = yl; y <= yr; y++) {
                if (a[xr][y] == 2) in--;
                if (a[xr + 1][y] == 4) in++;
            }
        if (yl != 1)
            for (int x = xl; x <= xr; x++) {
                if (a[x][yl - 1] == 1) in++;
                if (a[x][yl] == 3) in--;
            }
        if (yr != 2 * n + 1)
            for (int x = xl; x <= xr; x++) {
                if (a[x][yr] == 1) in--;
                if (a[x][yr + 1] == 3) in++;
            }
        return in > 0;
    };

    bool t = true;
    while (true) {
        assert(xl < xr && yl < yr);
        if (t & 1) {
            int ym = (yl + yr) >> 1;

            [&](void) -> bool {
                if (abs(cx - xl) < abs(cx - xr))
                    for (int x = xl; x <= xr; x++) get(x, ym);
                else
                    for (int x = xr; x >= xl; x--) get(x, ym);
                if (abs(cx - xl) < abs(cx - xr))
                    for (int x = xl; x <= xr; x++) get(x, ym + 1);
                else
                    for (int x = xr; x >= xl; x--) get(x, ym + 1);

                return chk(xl, xr, ym + 1, yr);
            }()
                             ? (yl = ym + 1)
                             : (yr = ym);
        } else {
            int xm = (xl + xr) >> 1;

            [&](void) -> bool {
                if (abs(cy - yl) < abs(cy - yr))
                    for (int y = yl; y <= yr; y++) get(xm, y);
                else
                    for (int y = yr; y >= yl; y--) get(xm, y);
                if (abs(cy - yl) < abs(cy - yr))
                    for (int y = yl; y <= yr; y++) get(xm + 1, y);
                else
                    for (int y = yr; y >= yl; y--) get(xm + 1, y);

                return chk(xm + 1, xr, yl, yr);
            }()
                             ? (xl = xm + 1)
                             : (xr = xm);
        }
        t = !t;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    mp['.'] = 0;
    mp['>'] = 1;
    mp['v'] = 2;
    mp['<'] = 3;
    mp['^'] = 4;
    mp['G'] = 5;

    int _ = 1;
    while (_--) solve();

    return 0;
}
