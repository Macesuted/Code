/**
 * @file 141-Bob.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Bob.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

namespace BOB {
vector<vector<int>> graph;
vector<int> ans, deg, c;
vector<bool> vis;
}  // namespace BOB
using namespace BOB;

void dfs(int p, int col) {
    ans[p] = col, vis[p] = true;
    for (auto i : graph[p])
        if (deg[i] >= 8 && c[p] == c[i] && !vis[i]) dfs(i, col ^ 1);
    return;
}

vector<int> Bob(int n, int m, vector<int> U, vector<int> V, vector<int> X) {
    ans.resize(n), graph.resize(n), deg.resize(n), c.resize(n), vis.resize(n);
    for (int i = 0; i < m; i++) graph[U[i]].push_back(V[i]), graph[V[i]].push_back(U[i]), deg[U[i]]++, deg[V[i]]++;
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (deg[i] < 8) que.push(i);
    vector<int> rec;
    while (!que.empty()) {
        int p = que.front();
        que.pop(), rec.push_back(p);
        for (auto i : graph[p])
            if (--deg[i] == 7) que.push(i);
    }
    for (int i = 0, p = 0; i < n; i++)
        if (deg[i] >= 8) c[i] = X[p] << 1 | X[p + 1], p += 2;
    for (int i = 0; i < n; i++)
        if (deg[i] >= 8 && !vis[i]) dfs(i, c[i] << 1);
    reverse(rec.begin(), rec.end());
    for (auto i : rec) {
        int S = 0;
        for (auto j : graph[i])
            if (vis[j]) S |= 1 << ans[j];
        while (S >> ans[i] & 1) ans[i]++;
        vis[i] = true;
    }
    return ans;
}