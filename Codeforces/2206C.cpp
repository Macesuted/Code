/**
 * @file 2206C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005
#define maxm 200005

unordered_map<int, int> graph[maxn];
bool vis[maxn];
int v[maxm];

queue<int> que;

void dfs(int p) {
    vis[p] = true;

    int cnt = graph[p].size();
    while (true) {
        if (que.empty() || !graph[p].count(que.front())) break;
        int q = que.front();
        que.pop();
        v[graph[p][q]] = cnt--;
        dfs(q);
    }

    for (auto [q, id] : graph[p])
        if (!vis[q]) cout << "impossible" << endl, exit(0);

    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x][y] = graph[y][x] = i, v[i] = 1;

    int r;
    cin >> r;

    if (r != 1) return cout << "impossible" << endl, void();

    for (int i = 1, x; i < n; i++) cin >> x, que.push(x);

    dfs(r);

    for (int i = 1; i <= m; i++) cout << v[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}