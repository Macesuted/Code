/**
 * @file 3787.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 17

typedef tuple<int, int, int, int> tiiii;

const int way[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};
const char ch[4] = {'D', 'R', 'U', 'L'};

int a[maxn][maxn], fo[maxn][maxn], dist[16][maxn][maxn][2175];
tiiii last[16][maxn][maxn][2175];
bool upd[16][maxn][maxn][2175];

bool vis[20][20];
map<string, int> valid[9];
string str[9][2175];
string val;
queue<tiiii> que[9];

void dfs(int p, int tx, int ty) {
    str[p][valid[p][val] = valid[p].size()] = val;
    if (p == 8) return;
    for (int i = 0; i < 4; i++) {
        int x = tx + way[0][i], y = ty + way[1][i];
        if (vis[x][y]) continue;
        vis[x][y] = true, val.push_back(ch[i]), dfs(p + 1, x, y), val.pop_back(), vis[x][y] = false;
    }
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) a[i][j + 1] = s[j] - '0';
    }
    string stat;
    int sx, sy;
    cin >> sx >> sy;
    for (int i = 2, lx = sx, ly = sy; i <= 4; i++) {
        int tx, ty;
        cin >> tx >> ty;
        for (int t = 0; t < 4; t++)
            if (lx + way[0][t] == tx && ly + way[1][t] == ty) {
                stat.push_back(ch[t]);
                break;
            }
        lx = tx, ly = ty;
    }
    int q;
    cin >> q;
    for (int i = 1, tx, ty; i <= q; i++) cin >> tx >> ty, fo[tx][ty] = i;
    memset(dist, 0x3f, sizeof(dist));
    que[dist[0][sx][sy][valid[4][stat]] = 0].emplace(0, sx, sy, valid[4][stat]),
        last[0][sx][sy][valid[4][stat]] = {-1, -1, -1, -1};
    for (int d = 0;; d++) {
        bool check = true;
        for (int i = 0; i < 9; i++)
            if (!que[i].empty()) check = false;
        if (check) break;
        int td = d % 9;
        while (!que[td].empty()) {
            int s, x, y, statid;
            tie(s, x, y, statid) = que[td].front(), que[td].pop();
            if (upd[s][x][y][statid]) continue;
            upd[s][x][y][statid] = true;
            if (s == (1 << q) - 1) {
                cout << d << endl;
                int ps = s, px = x, py = y, pstat = statid;
                stack<char> S;
                while (~get<0>(last[ps][px][py][pstat])) {
                    int ts, tx, ty, tstat;
                    tie(ts, tx, ty, tstat) = last[ps][px][py][pstat];
                    for (int t = 0; t < 4; t++)
                        if (tx + way[0][t] == px && ty + way[1][t] == py) {
                            S.push(ch[t]);
                            break;
                        }
                    ps = ts, px = tx, py = ty, pstat = tstat;
                }
                while (!S.empty()) cout << S.top(), S.pop();
                cout << endl;
                return;
            }
            int sl = 4 + __builtin_popcount(s);
            string stat = str[sl][statid];
            for (int t = 0; t < 4; t++) {
                int ts = s, tx = x + way[0][t], ty = y + way[1][t];
                string sta = ch[t ^ 2] + stat;
                if (fo[tx][ty]) ts |= 1 << (fo[tx][ty] - 1);
                if (!fo[tx][ty]) sta.pop_back();
                if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] == 0 || !valid[sta.size() + 1].count(sta))
                    continue;
                int staid = valid[sta.size() + 1][sta];
                if (dist[ts][tx][ty][staid] <= d + abs(a[x][y] - a[tx][ty]) + 1) continue;
                dist[ts][tx][ty][staid] = d + abs(a[x][y] - a[tx][ty]) + 1, last[ts][tx][ty][staid] = {s, x, y, statid};
                que[(td + abs(a[x][y] - a[tx][ty]) + 1) % 9].emplace(ts, tx, ty, staid);
            }
        }
    }
    cout << "No solution." << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    vis[10][10] = true, dfs(1, 10, 10);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}