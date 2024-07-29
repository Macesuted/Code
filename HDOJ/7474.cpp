/**
 * @file 7474.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define maxn 52

bool mem1;

const int way[2][4] = {{0, 0, +1, -1}, {+1, -1, 0, 0}};

int f[maxn][maxn][maxn][11][11][6], g[maxn][maxn][maxn];
string a[maxn];

bool mem2;

void solve(void) {
    int n, m, k, hp;
    cin >> n >> m >> k >> hp;

    a[0] = a[n + 1] = string(n + 2, '#');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = '#' + a[i] + '#';

    int sx, sy, tx, ty;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j] == 'P')
                sx = i, sy = j, a[i][j] = '.';
            else if (a[i][j] == 'E')
                tx = i, ty = j, a[i][j] = '.';

    for (int t = 0; t <= m - k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int dx = 0; dx <= 2 * hp; dx++)
                    for (int dy = 0; dy <= 2 * hp; dy++)
                        for (int vhp = 0; vhp <= hp; vhp++) f[t][i][j][dx][dy][vhp] = 0;

    for (int t = 0; t <= k; t++)
        for (int i = 0; i <= n + 1; i++)
            for (int j = 0; j <= n + 1; j++) g[t][i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j] == '.') g[0][i][j] = 1;
    for (int t = 1; t <= k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (a[i][j] == '.')
                    g[t][i][j] =
                        ((int64_t)g[t - 1][i - 1][j] + g[t - 1][i + 1][j] + g[t - 1][i][j - 1] + g[t - 1][i][j + 1]) % mod;

    f[0][sx][sy][hp][hp][hp] = 1;

    int64_t ans = 0;
    for (int t = 0; t < m - k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int dx = 0; dx <= 2 * hp; dx++)
                    for (int dy = 0; dy <= 2 * hp; dy++)
                        for (int vhp = 1; vhp <= hp; vhp++) {
                            if (!f[t][i][j][dx][dy][vhp]) continue;
                            int ox = i - sx + tx + (dx - hp), oy = j - sy + ty + (dy - hp);
                            for (int x = 0; x < 4; x++) {
                                int Px = i + way[0][x], Py = j + way[1][x], Ex = ox + way[0][x], Ey = oy + way[1][x];
                                int Ehp = vhp, Edx = dx, Edy = dy;
                                if (a[Px][Py] == '#') continue;
                                if (a[Ex][Ey] == '#')
                                    Ex -= way[0][x], Ey -= way[1][x], Ehp--, Edx -= way[0][x], Edy -= way[1][x];
                                if (Ehp == 0) {
                                    ans = (ans + (int64_t)f[t][i][j][dx][dy][vhp] * g[k][Px][Py]) % mod;
                                    continue;
                                }
                                f[t + 1][Px][Py][Edx][Edy][Ehp] =
                                    (f[t + 1][Px][Py][Edx][Edy][Ehp] + f[t][i][j][dx][dy][vhp]) % mod;
                            }
                        }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}