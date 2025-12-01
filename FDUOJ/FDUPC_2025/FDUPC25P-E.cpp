/**
 * @file FDUPC25P-E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-27
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

#define maxn 305

using pii = pair<int, int>;

const int dw[4][2] = {{+1, 0}, {-1, 0}, {0, +1}, {0, -1}};

string s[maxn];
int dist[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = ' ' + s[i] + ' ';

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) dist[i][j] = INT_MAX;

    int q;
    cin >> q;
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        assert(s[x][y] == '.');
        if (op == 1) {
            queue<pii> que;
            dist[x][y] = 0, que.emplace(x, y);
            while (!que.empty()) {
                auto [x, y] = que.front();
                que.pop();
                for (int t = 0; t < 4; t++) {
                    int tx = x + dw[t][0], ty = y + dw[t][1];
                    if (tx < 1 || tx > n || ty < 1 || ty > n || s[tx][ty] == '#' || dist[tx][ty] <= dist[x][y] + 1) continue;
                    dist[tx][ty] = dist[x][y] + 1, que.emplace(tx, ty);
                }
            }
        } else
            cout << (dist[x][y] == INT_MAX ? -1 : dist[x][y]) << endl;
    }

    return;
}

bool mem2;

int main() {
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
