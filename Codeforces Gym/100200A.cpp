/**
 * @file 100200A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
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
class Dinic {
   private:
    struct Edge {
        int to, cap, rev;
        bool mark;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist, rdist;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = INT_MAX, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + 1) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T] != INT_MAX;
    }
    void rbfs(void) {
        for (int i = 1; i <= n; i++) rdist[i] = INT_MAX;
        que.push(T), rdist[T] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (graph[i.to][i.rev].cap && rdist[i.to] > rdist[p] + 1) rdist[i.to] = rdist[p] + 1, que.push(i.to);
        }
        return;
    }
    int64_t dfs(int p, int64_t rest) {
        if (p == T) return rest;
        int64_t use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, (int64_t)i->cap)))) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, use += c, rest -= c;
        }
        return use;
    }

   public:
    void resize(int _n) { return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1), rdist.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size(), false}),
               graph[to].push_back(Edge{from, cap, (int)graph[from].size() - 1, false});
    }
    int64_t maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int64_t ans = 0;
        while (bfs()) ans += dfs(S, INT64_MAX);
        return ans;
    }
    bool solve(void) {
        bfs(), rbfs();
        for (int p = 1; p <= n; p++)
            for (auto &e : graph[p]) {
                if (!e.cap && dist[p] != INT_MAX && rdist[e.to] != INT_MAX) e.mark = true;
            }

        for (int i = 1; i <= n; i++) dist[i] = 0;
        que.push(S);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (!i.mark && !dist[i.to]) dist[i.to] = 1, que.push(i.to);
        }

        return dist[T];
    }
};

void solve(void) {
    int n, m, S, T;
    cin >> n >> m >> S >> T;

    Dinic dnc;
    dnc.resize(n);
    for (int i = 1, x, y, f; i <= m; i++) cin >> x >> y >> f, dnc.addEdge(x, y, f);

    dnc.maxFlow(S, T);

    cout << (dnc.solve() ? "AMBIGUOUS" : "UNIQUE") << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("attack.in", "r", stdin), freopen("attack.out", "w", stdout);
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