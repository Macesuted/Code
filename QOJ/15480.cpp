/**
 * @file 15480.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 305

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

const int dw[4][2] = {{0, -1}, {-1, 0}, {0, +1}, {+1, 0}};
const int coef[4][2] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

string a[maxn];
int dist[maxn][maxn];
int xdist[maxn][maxn][maxn][4];
int ans[maxn][maxn];

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;

    a[0] = a[n + 1] = string(m + 2, '#');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = '#' + a[i] + '#';

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans[i][j] = -1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != 'C' || dist[i][j]) continue;

            priority_queue<tiii, vector<tiii>, less<tiii>> que;
            vector<pii> nodes;
            que.emplace(dist[i][j] = k + 1, i, j);
            while (!que.empty()) {
                auto [d, x, y] = que.top();
                que.pop();
                if (d != dist[x][y]) continue;
                nodes.emplace_back(x, y);
                if (d == 1) continue;
                for (int t = 0; t < 4; t++) {
                    int tx = x + dw[t][0], ty = y + dw[t][1];
                    if (a[tx][ty] != '#' && dist[tx][ty] < d - 1) {
                        dist[tx][ty] = a[tx][ty] == 'C' ? k + 1 : d - 1;
                        que.emplace(dist[tx][ty], tx, ty);
                    }
                }
            }

            for (auto [x, y] : nodes)
                if (a[x][y] == '.') dist[x][y] = 0;

            int w[4] = {int(-1e9), int(-1e9), int(-1e9), int(-1e9)};
            for (auto [x, y] : nodes)
                for (int t = 0; t < 4; t++) w[t] = max(w[t], x * coef[t][0] + y * coef[t][1]);

            for (auto [x, y] : nodes)
                for (int t = 0; t < 4; t++) ans[x][y] = max(ans[x][y], w[t] - x * coef[t][0] - y * coef[t][1]);
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '.')
                for (int t = 0; t < 4; t++) xdist[1][i][j][t] = i * coef[t][0] + j * coef[t][1];

    for (int d = 2; d <= k + 1; d++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (a[i][j] != '.') continue;

                for (int u = 0; u < 4; u++) xdist[d][i][j][u] = xdist[d - 1][i][j][u];
                for (int t = 0; t < 4; t++) {
                    int di = i + dw[t][0], dj = j + dw[t][1];
                    if (a[di][dj] == '.')
                        for (int u = 0; u < 4; u++) xdist[d][i][j][u] = max(xdist[d][i][j][u], xdist[d - 1][di][dj][u]);
                }
            }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '.')
                for (int t = 0; t < 4; t++) ans[i][j] = max(ans[i][j], xdist[k + 1][i][j][t] - i * coef[t][0] - j * coef[t][1]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << ans[i][j] << ' ';
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
