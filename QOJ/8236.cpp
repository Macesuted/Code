/**
 * @file 8236.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 3005

typedef tuple<int, int, int> tiii;

const int way[2][4] = {{0, 0, +1, -1}, {+1, -1, 0, 0}};

int a[maxn][maxn], dist[maxn][maxn];
bool vis[maxn][maxn];

void solve(void) {
    int n, m, k, sx, sy;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = 0, dist[i][j] = 1e9, vis[i][j] = false;
    for (int i = 1, x, y; i <= k; i++) {
        cin >> x >> y, a[x][y] = k - i + 1;
        if (i == 1) sx = x, sy = y;
    }
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
            if (s[j - 1] == '#') a[i][j] = 1e9;
    }

    priority_queue<tiii, vector<tiii>, greater<tiii>> que;
    que.emplace(dist[sx][sy] = 0, sx, sy);
    while (!que.empty()) {
        auto [d, x, y] = que.top();
        que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        for (int t = 0; t < 4; t++) {
            int tx = x + way[0][t], ty = y + way[1][t];
            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            int v = max(dist[x][y] + 1, a[tx][ty]);
            if (dist[tx][ty] > v) que.emplace(dist[tx][ty] = v, tx, ty);
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (dist[i][j] == 1e9) dist[i][j] = 0;
    uint64_t ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) ans += (uint64_t)dist[i][j] * (uint64_t)dist[i][j];
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
