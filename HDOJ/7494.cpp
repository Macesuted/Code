/**
 * @file 7494.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

vector<vector<int>> graph;

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) {
        if (graph[i].size() != 2) continue;
        int p = graph[i][0], q = graph[i][1], target = n - 1;
        if (graph[p].size() == 2) {
            int p2 = graph[p][graph[p][0] == i];
            if (graph[p2].size() != 1) p = p2, target--;
        }
        if (graph[q].size() == 2) {
            int q2 = graph[q][graph[q][0] == i];
            if (graph[q2].size() != 1) q = q2, target--;
        }
        if ((int)graph[p].size() + (int)graph[q].size() == target) return cout << "Yes" << endl, void();
    }
    return cout << "No" << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}