/**
 * @file 3304.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

using pli = pair<int64_t, int>;

class Dinic {
   private:
    struct Edge {
        int to, cap, rev;
        int64_t cost;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int64_t> dist, ht;
    vector<bool> vis;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = INT64_MIN, vis[i] = false, cur[i] = graph[i].begin();
        priority_queue<pli, vector<pli>, less<pli>> que;
        que.emplace(dist[S] = 0, S);
        while (!que.empty()) {
            auto [dis, p] = que.top();
            que.pop();
            if (vis[p]) continue;
            vis[p] = true;
            for (auto e : graph[p])
                if (e.cap && dist[e.to] + ht[e.to] < dis + ht[p] + e.cost)
                    que.emplace(dist[e.to] = dis + ht[p] + e.cost - ht[e.to], e.to);
        }
        for (int i = 1; i <= n; i++) vis[i] = false;
        return dist[T] != INT64_MIN;
    }

    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        vis[p] = true;
        int used = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] + ht[i->to] != dist[p] + ht[p] + i->cost || vis[i->to]) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = 1;
            i->cap -= c, graph[i->to][i->rev].cap += c, used += c, rest -= c;
        }
        vis[p] = false;
        return used;
    }

   public:
    void resize(int _n) {
        return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1), ht.resize(n + 1);
    }
    void addEdge(int from, int to, int cap, int64_t cost) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size(), cost}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1, -cost});
    }
    int64_t flow2(int _S, int _T) {
        S = _S, T = _T;

        for (int i = 1; i <= n; i++) ht[i] = 0;
        for (int i = 1; i <= n; i++)
            for (auto e : graph[i])
                if (e.cap) ht[e.to] = max(ht[e.to], ht[i] + e.cost);

        int64_t flow = 2, ans = 0;
        while (flow && bfs()) {
            int64_t c = dfs(S, flow);
            flow -= c, ans += c * (dist[T] + ht[T]);
            for (int i = 1; i <= n; i++) ht[i] += dist[i];
        }
        return ans;
    }
};

void solve(void) {
    int n;
    cin >> n;

    Dinic dnc;
    int V = 500001;
    dnc.resize(V);

    for (int i = 1; i < V; i++) dnc.addEdge(i, i + 1, 2, 0);

    for (int i = 1; i <= n; i++) {
        int x, y;
        int64_t w;
        cin >> x >> y >> w;
        dnc.addEdge(x, y + 1, 1, w);
    }

    cout << dnc.flow2(1, V) << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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