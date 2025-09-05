/**
 * @file 14021.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 4005

vector<vector<int>> graph;
bool up[maxn];

void dfs(int p) {
    up[p] = true;
    for (auto q : graph[p]) {
        dfs(q);
        if (up[q]) up[p] = false;
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;

    graph.clear(), graph.resize(n + 1);
    for (int i = 2, fa; i <= n; i++) cin >> fa, graph[fa].push_back(i);

    dfs(1);

    cout << "Yes" << endl;
    cout << n - 1 << endl;
    for (int i = 2; i <= n; i++) {
        int x = 1, y = i;
        if (up[i]) swap(x, y);
        cout << x << ' ' << y << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}