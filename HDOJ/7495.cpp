/**
 * @file 7495.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 10005

vector<vector<int>> graph;
int cnt[maxn], deg[maxn], tot, tot1;

void update(int p, int delt) {
    if (cnt[p] == deg[p]) (deg[p] == 1 ? tot1 : tot) += delt * (cnt[p] + 1);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    graph.clear(), graph.resize(n + 1), tot = tot1 = 0;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) cnt[i] = 0, deg[i] = graph[i].size();
    for (int i = 1; i <= n; i++)
        if (graph[i].size() == 1) cnt[graph[i][0]]++;
    for (int i = 1; i <= n; i++) update(i, +1);
    bool vis = false;
    for (int i = 1; i <= n; i++) {
        update(i, -1);
        if (graph[i].empty()) {
            if (tot + tot1 / 2 == n - 1) cout << i << ' ', vis = true;
        } else if (graph[i].size() == 1) {
            int j = graph[i][0];
            update(graph[i][0], -1), cnt[graph[i][0]]--, deg[graph[i][0]]--, update(graph[i][0], +1);
            if (graph[j].size() == 2) {
                int x = graph[j][graph[j][0] == i];
                update(x, -1), cnt[x]++, update(x, +1);
            }
            if (tot + tot1 / 2 == n - 1) cout << i << ' ', vis = true;
            if (graph[j].size() == 2) {
                int x = graph[j][graph[j][0] == i];
                update(x, -1), cnt[x]--, update(x, +1);
            }
            update(graph[i][0], -1), cnt[graph[i][0]]++, deg[graph[i][0]]++, update(graph[i][0], +1);
        } else {
            for (auto j : graph[i]) {
                update(j, -1), deg[j]--, update(j, +1);
                if (graph[j].size() == 2) {
                    int x = graph[j][graph[j][0] == i];
                    update(x, -1), cnt[x]++, update(x, +1);
                }
            }

            if (tot + tot1 / 2 == n - 1) cout << i << ' ', vis = true;

            for (auto j : graph[i]) {
                update(j, -1), deg[j]++, update(j, +1);
                if (graph[j].size() == 2) {
                    int x = graph[j][graph[j][0] == i];
                    update(x, -1), cnt[x]--, update(x, +1);
                }
            }
        }
        update(i, +1);
    }
    if (!vis) cout << -1;
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}