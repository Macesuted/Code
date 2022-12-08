/**
 * @file 3291.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-08
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

#define maxn 405
#define maxN 700005

typedef pair<int64_t, int> pli;

vector<vector<pli>> sgraph, graph;
int n, m;
int64_t dist[maxN];
bool vis[maxN], mark[maxN];
priority_queue<pli, vector<pli>, greater<pli>> que;

int _(int x, int y, int t = 0) { return t * (n + 1) * (m + 1) + x * (m + 1) + y; }
void modifyEdge(int x, int y, int64_t v) {
    for (auto &i : graph[x])
        if (i.second == y) i.first = v;
    for (auto &i : graph[y])
        if (i.second == x) i.first = v;
    return;
}
void dfs(int p) {
    if (vis[p]) return;
    vis[p] = true;
    int x = p / (m + 1), y = p % (m + 1);
    for (auto i : sgraph[p])
        if (dist[i.second] == dist[p] + i.first) {
            dfs(i.second);
            int tx = i.second / (m + 1), ty = i.second % (m + 1);
            if (mark[i.second]) {
                if (tx == x)
                    if (ty < y)
                        modifyEdge(_(tx, ty, 1), _(tx, ty, 2), 1e18), modifyEdge(_(x, y, 0), _(x, y, 3), 1e18);
                    else
                        modifyEdge(_(x, y, 1), _(x, y, 2), 1e18), modifyEdge(_(tx, ty, 0), _(tx, ty, 3), 1e18);
                else if (tx < x)
                    modifyEdge(_(tx, ty, 2), _(tx, ty, 3), 1e18), modifyEdge(_(x, y, 0), _(x, y, 1), 1e18);
                else
                    modifyEdge(_(x, y, 2), _(x, y, 3), 1e18), modifyEdge(_(tx, ty, 0), _(tx, ty, 1), 1e18);
                mark[p] = true;
            }
        }
    return;
}

void solve(void) {
    cin >> n >> m;
    auto addEdge = [&](int x, int y, int64_t v) { return graph[x].emplace_back(v, y), graph[y].emplace_back(v, x); };
    graph.resize(_(n, m, 3) + 1), sgraph.resize(_(n, m) + 1);
    addEdge(_(0, 0, 1), _(0, 0, 2), 0), addEdge(_(0, 0, 2), _(0, 0, 3), 0);
    for (int i = 0; i <= n; i++)
        for (int j = (i == 0); j <= m; j++)
            for (int t = 0; t < 4; t++) addEdge(_(i, j, t), _(i, j, (t + 1) % 4), 0);
    for (int i = 1, v; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> v;
            if (v) {
                mark[_(i - 1, j - 1)] = true;
                modifyEdge(_(i - 1, j - 1, 1), _(i - 1, j - 1, 2), 1e18);
                modifyEdge(_(i - 1, j - 1, 2), _(i - 1, j - 1, 3), 1e18);
                modifyEdge(_(i - 1, j, 0), _(i - 1, j, 3), 1e18);
                modifyEdge(_(i - 1, j, 2), _(i - 1, j, 3), 1e18);
                modifyEdge(_(i, j, 0), _(i, j, 1), 1e18);
                modifyEdge(_(i, j, 3), _(i, j, 0), 1e18);
                modifyEdge(_(i, j - 1, 1), _(i, j - 1, 2), 1e18);
                modifyEdge(_(i, j - 1, 0), _(i, j - 1, 1), 1e18);
            }
        }
    for (int i = 1, v; i <= n; i++)
        for (int j = 0; j <= m; j++)
            cin >> v, addEdge(_(i - 1, j, 3), _(i, j, 0), v), addEdge(_(i - 1, j, 2), _(i, j, 1), v),
                sgraph[_(i - 1, j)].emplace_back(v, _(i, j)), sgraph[_(i, j)].emplace_back(v, _(i - 1, j));
    for (int i = 0, v; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> v, addEdge(_(i, j - 1, 1), _(i, j, 0), v), addEdge(_(i, j - 1, 2), _(i, j, 3), v),
                sgraph[_(i, j - 1)].emplace_back(v, _(i, j)), sgraph[_(i, j)].emplace_back(v, _(i, j - 1));
    for (int i = 0; i <= _(n, m); i++) dist[i] = INT64_MAX;
    que.emplace(dist[_(0, 0)] = 0, _(0, 0));
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : sgraph[p])
            if (dist[i.second] > dist[p] + i.first) que.emplace(dist[i.second] = dist[p] + i.first, i.second);
    }
    for (int i = 0; i <= _(n, m); i++) vis[i] = false;
    dfs(_(0, 0));
    for (int i = 0; i <= _(n, m, 3); i++) dist[i] = INT64_MAX, vis[i] = false;
    que.emplace(dist[_(0, 0, 1)] = 0, _(0, 0, 1));
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.second] > dist[p] + i.first) que.emplace(dist[i.second] = dist[p] + i.first, i.second);
    }
    cout << dist[_(0, 0, 3)] << endl;
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