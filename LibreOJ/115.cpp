/**
 * @file 115.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

#define maxm 15000

int ans[maxm];

class Dinic {
   private:
    struct Edge {
        int to, rev;
        int64_t cap;
        int id;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int64_t> dist, preF;
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
    void resize(int _n) { return graph.resize((n = _n + 2) + 1), cur.resize(n + 1), dist.resize(n + 1), preF.resize(n + 1); }
    void addEdge(int from, int to, int64_t cap, int id, int lowf = 0) {
        preF[from] -= lowf, preF[to] += lowf, cap -= lowf, ans[id] += lowf;
        return graph[from].push_back(Edge{to, (int)graph[to].size(), cap, id}),
               graph[to].push_back(Edge{from, (int)graph[from].size() - 1, 0, -id});
    }
    bool preCheck(void) {
        S = n - 1, T = n;
        int64_t tot = 0;
        for (int i = 1; i <= n; i++) {
            if (preF[i] < 0) addEdge(i, T, -preF[i], -1);
            if (preF[i] > 0) addEdge(S, i, preF[i], -1), tot += preF[i];
        }
        int64_t ans = 0;
        while (bfs()) ans += dfs(S, INT64_MAX);
        for (int i = 1; i <= n; i++)
            for (auto e : graph[i])
                if (e.id > 0) ::ans[e.id] += graph[e.to][e.rev].cap;
        return ans == tot;
    }
    int64_t maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int64_t ans = 0;
        while (bfs()) ans += dfs(S, INT64_MAX);
        return ans;
    }
};

bool mem1;

void solve(void) {
    int n, m;
    cin >> n >> m;

    Dinic dnc;
    dnc.resize(n);
    for (int i = 1, x, y, l, c; i <= m; i++) cin >> x >> y >> l >> c, dnc.addEdge(x, y, c, i, l);
    if (!dnc.preCheck()) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    for (int i = 1; i <= m; i++) cout << ans[i] << endl;
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
