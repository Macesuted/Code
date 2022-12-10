/**
 * @file 2637.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int n, m, dis[2][maxn], deg[maxn], id[maxn];
bool vis[maxn], ban[maxn];
vector<vector<int>> graph;
vector<int> ring;
stack<int> S;

bool dfs(int p, int pre = -1) {
    S.push(p), vis[p] = true;
    for (auto i : graph[p]) {
        if (i == pre) continue;
        if (vis[i]) {
            while (S.top() != i) ring.push_back(S.top()), S.pop();
            ring.push_back(i);
            return true;
        }
        if (dfs(i, p)) return true;
    }
    return false;
}
void bfs(int p, int dis[]) {
    for (int i = 1; i <= n; i++) dis[i] = INT_MAX;
    queue<int> que;
    que.push(p), dis[p] = 0;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (ban[p]) continue;
        for (auto i : graph[p])
            if (dis[i] == INT_MAX) dis[i] = dis[p] + 1, que.push(i);
    }
    return;
}
bool check(int s1, int s2) {
    for (int i = 1; i <= n; i++) ban[i] = false;
    bfs(s1, dis[0]), bfs(s2, dis[1]);
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (dis[0][i] == dis[0][j] || dis[1][i] == dis[1][j]) return false;
    for (int i = 1; i <= n; i++) vis[i] = false;
    queue<pii> que;
    for (int i = 1; i <= n; i++)
        if (dis[0][i] == dis[1][i]) que.emplace(i, i), vis[i] = true;
    while (!que.empty()) {
        auto [p1, p2] = que.front();
        que.pop();
        if ((id[p1] && id[p1] != p2) || (id[p2] && id[p2] != p1)) return false;
        id[p1] = p2, id[p2] = p1;
        if (p1 == s1 && p2 == s2) continue;
        int x = 0, y = 0;
        for (auto i : graph[p1])
            if (dis[0][i] + 1 == dis[0][p1]) {
                if (x) return false;
                x = i;
            }
        for (auto i : graph[p2])
            if (dis[1][i] + 1 == dis[1][p2]) {
                if (y) return false;
                y = i;
            }
        if (!x || !y || vis[x] != vis[y]) return false;
        deg[p1]++, deg[p2]++, deg[x]++, deg[y]++;
        if (vis[x]) continue;
        vis[x] = vis[y] = true, que.emplace(x, y);
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] != (int)graph[i].size() || deg[i] != deg[id[i]]) return false;
        if (id[i] == i) continue;
        set<int> S;
        for (auto j : graph[i]) S.insert(id[j]);
        for (auto j : graph[id[i]])
            if (!S.count(j)) return false;
    }
    return true;
}

bool solve(void) {
    cin >> n >> m, graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++)
        if (graph[i].empty()) return false;
    vector<int> pos;
    for (int i = 1; i <= n; i++)
        if (graph[i].size() == 1) pos.push_back(i);
    if (pos.empty()) {
        dfs(1);
        if (ring.size() & 1) return false;
        for (auto i : ring) ban[i] = true;
        int p = 1;
        while (p <= n && ban[p]) p++;
        if (p == n + 1) return m == n;
        bfs(p, dis[0]);
        for (auto i : ring)
            if (dis[0][i] != INT_MAX) pos.push_back(i);
    }
    if (pos.size() != 2) return false;
    return check(pos[0], pos[1]);
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}