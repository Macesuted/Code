/**
 * @file 81600H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 45

vector<vector<int>> graph;
int64_t conn[maxn];
int ans;

void dfs(int p, int64_t S = 0, int len = 0) {
    S |= (int64_t)1 << p, len++;
    ans = max(ans, len);
    for (auto q : graph[p])
        if (!(S >> q & 1) && (conn[q] & S) == ((int64_t)1 << p)) dfs(q, S, len);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    graph.clear(), graph.resize(n + 1);

    for (int i = 1; i <= n; i++) conn[i] = 0;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        graph[x].push_back(y), graph[y].push_back(x);
        conn[x] |= (int64_t)1 << y;
        conn[y] |= (int64_t)1 << x;
    }
    ans = 0;
    for (int i = 1; i <= n; i++) dfs(i);
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--) solve();

    return 0;
}