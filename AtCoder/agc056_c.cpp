/**
 * @file agc056_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-10
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

#define maxn 1000005

typedef pair<int, int> pii;

int dist[maxn];
vector<pii> graph[maxn];
priority_queue<pii, vector<pii>, greater<pii>> que;
bool vis[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) graph[i].emplace_back(i + 1, 1), graph[i + 1].emplace_back(i, 1);
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, graph[l - 1].emplace_back(r, 0), graph[r].emplace_back(l - 1, 0);
    memset(dist, 0x3f, sizeof(dist)), que.emplace(dist[0] = 0, 0);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }
    for (int i = 1; i <= n; i++) cout << (dist[i] - dist[i - 1] == -1);
    cout << endl;
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