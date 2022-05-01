/**
 * @file 101.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

class Dinic {
   private:
    struct Edge {
        int to, rev;
        int64_t cap;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
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
        return dist[T] < INT_MAX;
    }
    int64_t dfs(int p, int64_t rest) {
        if (p == T || !rest) return rest;
        int64_t use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest > use; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        return use;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), dist.resize(n + 1), cur.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, (int)graph[to].size(), cap}),
               graph[to].push_back(Edge{from, (int)graph[from].size() - 1, 0});
    }
    int64_t maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int64_t ans = 0;
        while (bfs()) ans += dfs(S, INT64_MAX);
        return ans;
    }
} dinic;

void solve(void) {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    dinic.resize(n);
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        dinic.addEdge(x, y, c);
    }
    cout << dinic.maxFlow(s, t) << endl;
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
