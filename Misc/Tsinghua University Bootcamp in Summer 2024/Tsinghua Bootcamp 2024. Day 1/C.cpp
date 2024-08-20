/**
 * @file C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

typedef pair<int, int> pii;

bool mem1;

const int way[2][4] = {{0, 0, +1, -1}, {+1, -1, 0, 0}};

int k[maxn * maxn], dx[maxn * maxn], dy[maxn * maxn];
int64_t a[maxn][maxn], dis[maxn][maxn];

void solve(void) {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    int64_t sumk = 0;
    for (int i = 1; i <= n * m; i++) cin >> k[i] >> dx[i] >> dy[i], a[dx[i]][dy[i]] = (sumk += k[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) dis[i][j] = INT64_MAX;
    queue<pii> que;
    dis[r][c] = 0, que.emplace(r, c);
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int t = 0; t < 4; t++) {
            int tx = x + way[0][t], ty = y + way[1][t];
            if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] <= dis[x][y] || dis[tx][ty] <= dis[x][y] + 1) continue;
            dis[tx][ty] = dis[x][y] + 1, que.emplace(tx, ty);
        }
    }
    sumk = 0;
    for (int i = 1; i <= n * m; i++) {
        sumk += k[i];
        if (sumk < dis[dx[i]][dy[i]]) continue;
        if ((sumk & 1) == (dis[dx[i]][dy[i]] & 1)) return cout << i << endl, void();
        bool chk = true;
        for (int t = 0; t < 4; t++) {
            int tx = dx[i] + way[0][t], ty = dy[i] + way[1][t];
            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            chk &= (a[tx][ty] < a[dx[i]][dy[i]]);
        }
        if (chk) return cout << i << endl, void();
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}