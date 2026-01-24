/**
 * @file 15469.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 85

const int dw[4][2] = {{0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

int n, m;
int a[maxn][maxn];

void fall(void) {
    for (int j = 1; j <= m; j++) {
        stack<pair<int, int>> rec;
        for (int i = 1; i <= n; i++)
            if (a[i][j] != -3) rec.emplace(a[i][j], i);
        for (int i = n; i >= 1; i--)
            if (rec.empty())
                a[i][j] = -3;
            else {
                auto [v, x] = rec.top();
                rec.pop();
                if (v == 0 && x != i) v = -2;
                a[i][j] = v;
            }
    }
    return;
}
bool stage1(void) {
    static bool era[maxn][maxn];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) era[i][j] = false;

    for (int i = 1; i <= n; i++)
        for (int j = 1, jr; j <= m; j = jr + 1) {
            jr = j;
            if (a[i][j] <= 0) continue;

            while (jr + 1 <= m && a[i][jr + 1] == a[i][jr]) jr++;
            if (jr <= j + 1) continue;

            for (int x = j; x <= jr; x++) era[i][x] = true;
        }

    for (int j = 1; j <= m; j++)
        for (int i = 1, ir; i <= n; i = ir + 1) {
            ir = i;
            if (a[i][j] <= 0) continue;

            while (ir + 1 <= n && a[ir + 1][j] == a[ir][j]) ir++;
            if (ir <= i + 1) continue;

            for (int x = i; x <= ir; x++) era[x][j] = true;
        }

    bool ret = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (era[i][j]) a[i][j] = -3, ret = true;

    fall();

    return ret;
}
bool stage2(void) {
    static bool era[maxn][maxn];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) era[i][j] = false;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != -2) continue;
            for (int t = 0; t < 4; t++) {
                int x = i, y = j;
                while (1 <= x && x <= n && 1 <= y && y <= m && a[x][y] != -1) {
                    era[x][y] = true;
                    x += dw[t][0], y += dw[t][1];
                }
            }
        }

    bool ret = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (era[i][j]) a[i][j] = -3, ret = true;

    fall();

    return ret;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    swap(a[x1][y1], a[x2][y2]);

    while (true) {
        while (stage1())
            ;
        if (!stage2()) break;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans += (a[i][j] == -3);

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
