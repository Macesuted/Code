/**
 * @file 100198E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-11
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

vector<pii> graph[maxn];
vector<int> pos[maxn];
int dis[maxn];

void solve(void) {
    int n, m, S, T;
    cin >> n >> m >> S >> T;

    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].emplace_back(y, i), graph[y].emplace_back(x, i);

    queue<int> que;
    que.push(S), dis[S] = 1;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto [q, id] : graph[p])
            if (!dis[q]) dis[q] = dis[p] + 1, que.push(q);
    }

    for (int i = 1; i <= n; i++)
        for (auto [j, id] : graph[i])
            if (dis[i] < dis[j]) pos[dis[j]].push_back(id);

    cout << dis[T] - 1 << endl;

    for (int i = 2; i <= dis[T]; i++) {
        cout << pos[i].size() << ' ';
        for (auto id : pos[i]) cout << ' ' << id;
        cout << endl;
    }

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("defence.in", "r", stdin), freopen("defence.out", "w", stdout);
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