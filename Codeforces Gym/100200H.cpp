/**
 * @file 100200H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 405

typedef pair<int, int> pii;

const int way[4][2] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};

int dist[maxn][maxn];
string a[maxn * 2];

void solve(void) {
    int n, m;
    cin >> n >> m, getline(cin, a[0]);

    a[0] = a[2 * n] = string(2 * m + 1, ' ');
    for (int i = 1; i < 2 * n; i++) getline(cin, a[i]), a[i] = ' ' + a[i], a[i].resize(2 * m + 1, ' ');

    queue<pii> que;
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++) dist[i][j] = 1e8;
    que.emplace(1, m), dist[1][m] = 0;
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int t = 0; t < 4; t++) {
            int tx = x + way[t][0], ty = y + way[t][1];
            if (a[2 * x - 1 + way[t][0]][2 * y - 1 + way[t][1]] != ' ' && dist[tx][ty] > dist[x][y] + 1)
                dist[tx][ty] = dist[x][y] + 1, que.emplace(tx, ty);
        }
    }

    int x = n - 1, y = 1, t = 0;
    if (a[2 * n - 2][1] == ' ' || dist[n - 1][1] > dist[n][2]) x = n, y = 2, t = 1;
    cout << "NE"[x == n] << endl;

    while (dist[x][y]) {
        if (a[2 * x - 1 + way[t][0]][2 * y - 1 + way[t][1]] != ' ' && dist[x + way[t][0]][y + way[t][1]] + 1 == dist[x][y])
            cout << 'F';
        else
            for (int nt = 0; nt < 4; nt++)
                if (a[2 * x - 1 + way[nt][0]][2 * y - 1 + way[nt][1]] != ' ' &&
                    dist[x + way[nt][0]][y + way[nt][1]] + 1 == dist[x][y]) {
                    cout << "LR"[(t + 1) % 4 == nt], t = nt;
                    break;
                }
        x += way[t][0], y += way[t][1];
    }

    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("straight.in", "r", stdin), freopen("straight.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}