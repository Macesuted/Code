/**
 * @file 7487.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

#define maxn 100005

int x[maxn], y[maxn], col[maxn], cnt[maxn];

vector<vector<int>> graph;
vector<set<int>> rc;

void dfs(int p, int c) {
    col[p] = c;
    for (auto i : graph[p])
        if (!col[i]) dfs(i, c);
    return;
}

void solve() {
    int n, m;
    cin >> n >> m;
    graph.clear(), graph.resize(n + 1), rc.clear(), rc.resize(n + 1);
    for (int i = 1; i < n; i++) cin >> x[i] >> y[i];
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x), rc[x].insert(y), rc[y].insert(x);
    for (int i = 1; i <= n; i++) col[i] = 0;
    int c = 0;
    for (int i = 1; i <= n; i++)
        if (!col[i]) dfs(i, ++c), cnt[c] = 1;
    for (int i = 1; i < n; i++) {
        if (col[x[i]] != col[y[i]]) continue;
        if (rc[x[i]].find(y[i]) != rc[x[i]].end()) continue;
        cnt[col[x[i]]] = 2;
    }
    int ans = 0;
    for (int i = 1; i <= c; i++) ans += cnt[i];
    cout << ans << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}