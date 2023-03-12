/**
 * @file 141-Alice.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Alice.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> Alice(int n, int m, vector<int> U, vector<int> V, vector<int> c) {
    vector<vector<int>> graph;
    vector<int> deg;
    graph.resize(n), deg.resize(n);
    for (int i = 0; i < m; i++) graph[U[i]].push_back(V[i]), graph[V[i]].push_back(U[i]), deg[U[i]]++, deg[V[i]]++;
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (deg[i] < 8) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (--deg[i] == 7) que.push(i);
    }
    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (deg[i] >= 8) ans.push_back(c[i] & 1), ans.push_back(c[i] >> 1 & 1);
    return ans;
}