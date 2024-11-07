/**
 * @file 7751.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 35
#define maxv 810005

typedef pair<int, int> pii;

const int way[4][2] = {{0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

string a[maxn];
pii nxt[maxv];
int dis[maxv];
bool vis[maxn][maxn];
vector<pii> graph[maxv], rgraph[maxv];

int _(pii x, pii y) { return (x.first - 1) * 27000 + (x.second - 1) * 900 + (y.first - 1) * 30 + (y.second - 1); }
pair<pii, pii> $(int v) { return {{v / 27000 + 1, v / 900 % 30 + 1}, {v / 30 % 30 + 1, v % 30 + 1}}; }

void solve(void) {
    int n, m;
    cin >> n >> m;

    a[0] = a[n + 1] = string(m + 2, '0');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = '0' + a[i] + '0';

    auto addEdge = [&](int p, int q, int t) { return graph[p].emplace_back(q, t), rgraph[q].emplace_back(p, t); };

    for (int ax = 1; ax <= n; ax++)
        for (int ay = 1; ay <= m; ay++)
            for (int bx = 1; bx <= n; bx++)
                for (int by = 1; by <= m; by++)
                    if (a[ax][ay] == '1' && a[bx][by] == '1')
                        for (int t = 0; t < 4; t++) {
                            int tax = ax + way[t][0], tay = ay + way[t][1];
                            if (a[tax][tay] == '0') tax = ax, tay = ay;
                            int tbx = bx - way[t][0], tby = by - way[t][1];
                            if (a[tbx][tby] == '1') addEdge(_({ax, ay}, {bx, by}), _({tax, tay}, {tbx, tby}), t);
                            if (a[bx + way[t][0]][by + way[t][1]] == '0')
                                addEdge(_({ax, ay}, {bx, by}), _({tax, tay}, {bx, by}), t);
                        }

    for (int i = 0; i < maxv; i++) nxt[i] = {-1, -1}, dis[i] = -1;
    queue<int> que;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++)
            if (a[x][y] == '1') nxt[_({x, y}, {x, y})] = {0, 4}, dis[_({x, y}, {x, y})] = 0, que.push(_({x, y}, {x, y}));
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto [q, t] : rgraph[p])
            if (dis[q] == -1) nxt[q] = {p, t}, dis[q] = dis[p] + 1, que.push(q);
    }

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    if (dis[_({sx, sy}, {tx, ty})] == -1) return cout << -1 << endl, void();
    mt19937 rnd(114514);
    while (clock() * 1000. / CLOCKS_PER_SEC < 900) {
        int rest = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (a[i][j] == '1') vis[i][j] = true, rest++;

        int p = _({sx, sy}, {tx, ty});
        string ans;
        rest -= vis[sx][sy], vis[sx][sy] = false;
        rest -= vis[tx][ty], vis[tx][ty] = false;

        while (rest) {
            bool mov = false;
            shuffle(graph[p].begin(), graph[p].end(), rnd);
            for (auto [q, t] : graph[p])
                if (dis[q] != -1 && (int)ans.size() + 1 + dis[q] <= int(1e6)) {
                    p = q, mov = true, ans.push_back("LRUD"[t]);
                    auto [u, v] = $(p);
                    rest -= vis[u.first][u.second], vis[u.first][u.second] = false;
                    rest -= vis[v.first][v.second], vis[v.first][v.second] = false;
                    break;
                }
            if (!mov) break;
        }
        if (rest) continue;
        while (dis[p]) ans.push_back("LRUD"[nxt[p].second]), p = nxt[p].first;
        string nans = ans;
        reverse(ans.begin(), ans.end());
        nans.append(ans.begin(), ans.end());
        cout << nans << endl;

        return;
    }
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}