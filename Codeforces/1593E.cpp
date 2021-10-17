/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 400005

typedef pair<int, int> pii;

vector<vector<int>> graph;
int deg[maxn];
bool vis[maxn];

void work(void) {
    int n, k;
    cin >> n >> k;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++) deg[i] = 0, vis[i] = false;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y), graph[y].push_back(x);
        deg[x]++, deg[y]++;
    }
    static queue<pii> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (deg[i] <= 1) que.push({i, 1});
    while (!que.empty()) {
        pii p = que.front();
        que.pop();
        vis[p.first] = true;
        if (p.second == k) continue;
        for (auto i : graph[p.first])
            if (!vis[i] && --deg[i] <= 1)
                que.push({i, p.second + 1});
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += !vis[i];
    cout << cnt << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}