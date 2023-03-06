/**
 * @file 4511.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

queue<int> que;
vector<vector<int>> graph;
int dist[maxn][2], deg[maxn];
bool ban[maxn];

void BFS(int n, int s, int d) {
    for (int i = 1; i <= n; i++) dist[i][d] = 1e9;
    dist[s][d] = 0, que.emplace(s);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (dist[i][d] == 1e9) dist[i][d] = dist[p][d] + 1, que.push(i);
    }
    return;
}

void solve(void) {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++) deg[i] = 0, ban[i] = false;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x), deg[x]++, deg[y]++;
    BFS(n, s, 0), BFS(n, t, 1);
    if (dist[t][0] == 1e9) return cout << "SAFE" << endl, void();
    for (int i = 1; i <= n; i++)
        if (deg[i] <= 1) que.push(i), ban[i] = true;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (--deg[i] <= 1 && !ban[i]) ban[i] = true, que.push(i);
    }
    for (int i = 1; i <= n; i++)
        if (!ban[i] && dist[i][0] < dist[i][1]) return cout << "SAFE" << endl, void();
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (dist[i][0] < dist[i][1]) ans = max(ans, dist[i][1]);
    return cout << ans * 2 << endl, void();
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ": ", solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}