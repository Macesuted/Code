/**
 * @file 1217D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
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

typedef pair<int, int> pii;

vector<pii> edges;
vector<int> graph[maxn];
int indeg[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, edges.emplace_back(x, y), graph[x].push_back(y), indeg[y]++;

    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto q : graph[p])
            if (!--indeg[q]) que.push(q);
    }

    for (int i = 1; i <= n; i++)
        if (indeg[i]) {
            cout << 2 << endl;
            for (int i = 0; i < m; i++) cout << 1 + (edges[i].first < edges[i].second) << ' ';
            cout << endl;
            return;
        }

    cout << 1 << endl;
    for (int i = 1; i <= m; i++) cout << 1 << ' ';
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