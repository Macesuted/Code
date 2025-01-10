/**
 * @file 100199B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

#define maxm 40005

int cap[maxm];

class Dinic {
   private:
    struct Edge {
        int to, cap, rev, id;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist, preF;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = INT_MAX, cur[i] = graph[i].begin();
        queue<int> que;
        dist[S] = 0, que.push(S);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap > 0 && dist[i.to] == INT_MAX) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T] != INT_MAX;
    }

    int dfs(int p, int rest) {
        if (p == T) return rest;
        int c, flow = 0;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (i->cap == 0 || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = -1;
            flow += c, rest -= c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        return flow;
    }

   public:
    void resize(int _n) { return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1), preF.resize(n + 1); }
    void addEdge(int from, int to, int cap, int low, int id) {
        preF[from] -= low, preF[to] += low, cap -= low, ::cap[id] += low;
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size(), id}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1, 0});
    }
    bool maxFlow(int _S, int _T) {
        S = _S, T = _T;

        for (int i = 1; i <= n; i++) {
            if (i == S || i == T) continue;
            if (preF[i] > 0) addEdge(S, i, preF[i], 0, 0);
            if (preF[i] < 0) addEdge(i, T, -preF[i], 0, 0);
        }

        while (bfs()) dfs(S, INT_MAX);

        for (int i = 1; i <= n; i++)
            for (auto e : graph[i])
                if (e.id) cap[e.id] += graph[e.to][e.rev].cap;

        for (auto e : graph[S])
            if (e.cap) return false;
        return true;
    }
};

void solve(void) {
    int n, m;
    cin >> n >> m;

    Dinic dnc;
    dnc.resize(n + 2);
    for (int i = 1, x, y, c, l; i <= m; i++) cin >> x >> y >> l >> c, dnc.addEdge(x, y, c, l, i);

    if (!dnc.maxFlow(n + 1, n + 2)) return cout << "NO" << endl, void();

    cout << "YES" << endl;
    for (int i = 1; i <= m; i++) cout << cap[i] << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("cooling.in", "r", stdin), freopen("cooling.out", "w", stdout);
#endif
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