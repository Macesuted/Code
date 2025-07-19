/**
 * @file 2122D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-19
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

#define maxn 5005

vector<vector<int>> graph;
bool vis[2][maxn];
int wait[2][maxn], ptr[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) vis[0][i] = false, wait[0][i] = 1e8, ptr[i] = 0;
    vis[0][1] = true, wait[0][1] = 0;
    for (int t = 0;; t++) {
        int x = t & 1;
        if (vis[x][n]) {
            cout << t << ' ' << wait[x][n] << endl;
            return;
        }
        for (int i = 1; i <= n; i++) vis[!x][i] = false, wait[!x][i] = 1e8;
        for (int i = 1; i <= n; i++) {
            if (!vis[x][i]) continue;
            vis[!x][i] = true, wait[!x][i] = min(wait[!x][i], wait[x][i] + 1);
            int j = graph[i][ptr[i]];
            vis[!x][j] = true, wait[!x][j] = min(wait[!x][j], wait[x][i]);
        }
        for (int i = 1; i <= n; i++)
            if (++ptr[i] == (int)graph[i].size()) ptr[i] = 0;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}