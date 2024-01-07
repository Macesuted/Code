/**
 * @file 1915G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-01-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;
typedef tuple<int64_t, int, int> tlii;

vector<int> s;
vector<vector<pii>> graph;
vector<vector<bool>> vis;
vector<vector<int64_t>> dist;
priority_queue<tlii, vector<tlii>, greater<tlii>> que;

void solve(void) {
    int n, m;
    cin >> n >> m;
    s.resize(n + 1), graph.resize(n + 1), vis.resize(n + 1), dist.resize(n + 1);
    for (int i = 1; i <= n; i++) vis[i].resize(n + 1, false), dist[i].resize(n + 1, INT64_MAX);
    for (int i = 1, x, y, d; i <= m; i++) cin >> x >> y >> d, graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
    for (int i = 1; i <= n; i++) cin >> s[i];
    que.emplace(dist[1][1] = 0, 1, 1);
    while (!que.empty()) {
        auto [d, x, y] = que.top();
        que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        for (auto [i, w] : graph[x]) {
            if (i == x) continue;
            int z = (s[y] < s[i] ? y : i);
            int64_t t = d + w * s[y];
            if (dist[i][z] > t) que.emplace(dist[i][z] = t, i, z);
        }
    }
    int64_t ans = INT64_MAX;
    for (int i = 1; i <= n; i++) ans = min(ans, dist[n][i]);
    cout << ans << endl;
    s.clear(), graph.clear(), vis.clear(), dist.clear();
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