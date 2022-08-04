/**
 * @file 102.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef pair<int, int> pii;

class Dinic {
   private:
    struct Edge {
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = INT_MAX, cur[i] = graph[i].begin(), vis[i] = false;
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) que.push(i.to), vis[i.to] = true;
                }
            vis[p] = false;
        }
        return dist[T] < INT_MAX;
    }
    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest > use; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + i->cost || vis[i->to]) continue;
            if (!(c = dfs(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        vis[p] = false;
        return use;
    }

   public:
    void resize(int _n) {
        return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1);
    }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    pii minCostFlow(int _S, int _T) {
        S = _S, T = _T;
        pii ans = {0, 0};
        while (bfs()) {
            int flow = dfs(S, INT_MAX);
            ans.first += flow, ans.second += flow * dist[T];
        }
        return ans;
    }
} dinic;

void solve(void) {
    int n, m;
    cin >> n >> m;
    dinic.resize(n);
    for (int i = 1; i <= m; i++) {
        int s, t, c, w;
        cin >> s >> t >> c >> w;
        dinic.addEdge(s, t, c, w);
    }
    pii ans = dinic.minCostFlow(1, n);
    cout << ans.first << ' ' << ans.second << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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