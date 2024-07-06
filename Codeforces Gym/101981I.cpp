/**
 * @file 101981I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

class Dinic {
   private:
    struct Edge {
        int to, flow, cap, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;
    int n;

    bool bfs(int S, int T) {
        for (int i = 1; i <= n; i++) dist[i] = INT_MAX, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap > i.flow && dist[i.to] > dist[p] + 1) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T] != INT_MAX;
    }
    int dfs(int p, int rest, int T) {
        if (p == T) return rest;
        int flow = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (i->cap == i->flow || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap - i->flow), T))) dist[i->to] = -1;
            rest -= c, flow += c, i->flow += c, graph[i->to][i->rev].flow -= c;
        }
        return flow;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, 0, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, cap, cap, (int)graph[from].size() - 1});
    }
    int maxFlow(int S, int T) {
        int ans = 0;
        while (bfs(S, T)) ans += dfs(S, INT_MAX, T);
        return ans;
    }
} dinic;

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    int O = n + m + 1, S = n + m + 2, T = n + m + 3;
    dinic.resize(T), dinic.addEdge(S, O, k);
    for (int i = 1, l, x; i <= n; i++) {
        dinic.addEdge(S, i, 1), dinic.addEdge(O, i, 1);
        cin >> l;
        while (l--) cin >> x, dinic.addEdge(i, n + x, 1);
    }
    for (int i = 1; i <= m; i++) dinic.addEdge(n + i, T, 1);
    cout << dinic.maxFlow(S, T) << endl;
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