/**
 * @file 102465I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

typedef pair<int, int> pii;

const int way8[2][8] = {{-1, -1, -1, 0, +1, +1, +1, 0}, {-1, 0, +1, +1, +1, 0, -1, -1}};

string a[maxn];
int n, m;
int sum[maxn][maxn], bel[maxn][maxn];

int getSum(int xl, int xr, int yl, int yr) { return sum[xr][yr] - sum[xr][yl - 1] - sum[xl - 1][yr] + sum[xl - 1][yl - 1]; }

void mark8(int x, int y, int id) {
    queue<pii> que;
    que.emplace(x, y), bel[x][y] = id;
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int t = 0; t < 8; t++) {
            int tx = x + way8[0][t], ty = y + way8[1][t];
            if (0 <= tx && tx <= n + 1 && 0 <= ty && ty <= m + 1 && a[tx][ty] == a[x][y] && !bel[tx][ty])
                bel[tx][ty] = id, que.emplace(tx, ty);
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cin >> m >> n;
    a[0] = a[n + 1] = string(m + 2, '#');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = '#' + a[i] + '#';

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) sum[i][j] = sum[i][j - 1] + (a[i][j] == '.');
    for (int j = 1; j <= m; j++)
        for (int i = 2; i <= n; i++) sum[i][j] += sum[i - 1][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            bool chk = (a[i][j] == '#');
            for (int t = 0; t < 8 && chk; t++) chk &= (a[i + way8[0][t]][j + way8[1][t]] == '.');
            if (chk) a[i][j] = '.';
        }

    mark8(0, 0, -1);

    int cnt[3] = {0, 0, 0};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != '#' || bel[i][j]) continue;

            mark8(i, j, +1);

            int x = 1, y = 1;
            while (!getSum(i, i, j, j + y)) y++;
            while (!getSum(i, i + x, j, j + y - 1)) x++;
            y -= 2 * x;

            if (getSum(i + 2 * x + 2 * y, i + 3 * x + 2 * y - 1, j + x, j + x + y - 1)) {
                cnt[0]++;
                continue;
            }

            if (getSum(i + x, i + 2 * x + 2 * y - 1, j + x + y, j + 2 * x + y - 1)) {
                cnt[2]++;
                continue;
            }
            cnt[1]++;
        }

    cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << endl;

    return 0;
}