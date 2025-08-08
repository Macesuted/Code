/**
 * @file C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 105
#define maxk 15
#define maxp 1000005

using pii = pair<int, int>;

const int way[4][2] = {{0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

string a[maxn];
int dist[maxn][maxn][4][maxk][4][maxk], d[maxn][maxn], w[maxp];
int64_t f[maxp][maxk];

void solve(void) {
    int n, k;
    cin >> n >> k;
    a[0] = a[n + 1] = string(n + 2, 'c');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = 'c' + a[i] + 'c';
    int X, Y;
    cin >> X >> Y;
    int p;
    string mov;
    cin >> p >> mov, mov = ' ' + mov;
    for (int i = 1; i <= p; i++) {
        string s = "LRUD";
        w[i] = 0;
        while (s[w[i]] != mov[i]) w[i]++;
    }

    auto gen = [&](int s, int t, int w, int i, int d = 0) -> pii {
        if (w == 0) return {s + i, t - d};
        if (w == 1) return {s + i, t + k - 1 + d};
        if (w == 2) return {s - d, t + i};
        if (w == 3) return {s + k - 1 + d, t + i};
        assert(false);
    };

    for (int xl = 1, xr = k; xr <= n; xl++, xr++)
        for (int yl = 1, yr = k; yr <= n; yl++, yr++)
            for (int t = 0; t < 4; t++)
                for (int id = 0; id < k; id++) {
                    auto [x, y] = gen(xl, yl, t, id, 0);

                    if (a[x][y] == 'c') continue;

                    for (int i = xl; i <= xr; i++)
                        for (int j = yl; j <= yr; j++) d[i][j] = INT_MAX;

                    queue<pii> que;
                    que.emplace(x, y), d[x][y] = 0;
                    while (!que.empty()) {
                        auto [x, y] = que.front();
                        que.pop();
                        for (int t = 0; t < 4; t++) {
                            int tx = x + way[t][0], ty = y + way[t][1];
                            if (xl <= tx && tx <= xr && yl <= ty && ty <= yr && a[tx][ty] == 'b' && d[tx][ty] > d[x][y] + 1)
                                que.emplace(tx, ty), d[tx][ty] = d[x][y] + 1;
                        }
                    }

                    for (int u = 0; u < 4; u++)
                        for (int i = 0; i < k; i++) {
                            auto [x, y] = gen(xl, yl, u, i, 0);
                            auto [tx, ty] = gen(xl, yl, u, i, 1);
                            if (a[tx][ty] == 'c') continue;
                            if (a[x][y] == 'c' || d[x][y] == INT_MAX)
                                dist[xl][yl][t][id][u][i] = INT_MAX;
                            else
                                dist[xl][yl][t][id][u][i] = d[x][y] + 1;
                        }
                }

    for (int i = 0; i < k; i++) f[0][i] = 0;

    for (int t = 1; t <= p; t++)
        for (int i = 0; i < k; i++) f[t][i] = 1e18;

    w[0] = w[1];

    for (int t = 1; t <= p; t++) {
        for (int i = 0; i < k; i++) {
            auto [fx, fy] = gen(X, Y, w[t - 1], i, 0);
            if (a[fx][fy] == 'c') continue;
            for (int j = 0; j < k; j++) {
                auto [tx, ty] = gen(X, Y, w[t], j, 1);
                if (a[tx][ty] == 'c') continue;
                f[t][j] = min(f[t][j], f[t - 1][i] + dist[X][Y][w[t - 1]][i][w[t]][j]);
            }
        }
        X += way[w[t]][0], Y += way[w[t]][1];
    }

    int64_t ans = INT64_MAX;
    for (int i = 0; i < k; i++) ans = min(ans, f[p][i]);
    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}