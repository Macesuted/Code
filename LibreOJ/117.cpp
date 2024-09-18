/**
 * @file 117.cpp
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

class Dinic {
   private:
    struct Edge {
        int to, rev;
        int64_t cap;
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
        int64_t used = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, (int64_t)i->cap)))) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, used += c, rest -= c;
        }
        return used;
    }

   public:
    void resize(int _n) { return graph.resize((n = _n + 2) + 1), cur.resize(n + 1), dist.resize(n + 1), preF.resize(n + 1); }
    void addEdge(int from, int to, int64_t cap, int64_t lowf = 0) {
        preF[from] -= lowf, preF[to] += lowf, cap -= lowf;
        return graph[from].push_back(Edge{to, (int)graph[to].size(), cap}),
               graph[to].push_back(Edge{from, (int)graph[from].size() - 1, 0});
    }
    int64_t maxFlow(int _S, int _T) {
        addEdge(_T, _S, INT64_MAX, 0);

        S = n - 1, T = n;
        int64_t tot = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            if (preF[i] < 0) addEdge(i, T, -preF[i]);
            if (preF[i] > 0) addEdge(S, i, preF[i]), tot += preF[i];
        }
        while (bfs()) ans += dfs(S, INT64_MAX);
        if (ans != tot) return -1;

        ans = 0, S = _S, T = _T;
        while (bfs()) ans += dfs(S, INT64_MAX);
        return ans;
    }
    int64_t minFlow(int _S, int _T) {
        addEdge(_T, _S, INT64_MAX, 0);

        S = n - 1, T = n;
        int64_t tot = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            if (preF[i] < 0) addEdge(i, T, -preF[i]);
            if (preF[i] > 0) addEdge(S, i, preF[i]), tot += preF[i];
        }
        while (bfs()) ans += dfs(S, INT64_MAX);
        if (ans != tot) return -1;

        ans = INT64_MAX, S = _T, T = _S;
        while (bfs()) ans -= dfs(S, INT64_MAX);
        return ans;
    }
};

bool mem1;

void solve(void) {
    int n, m, S, T;
    cin >> n >> m >> S >> T;

    Dinic dnc;
    dnc.resize(n);
    for (int i = 1, x, y, l, c; i <= m; i++) cin >> x >> y >> l >> c, dnc.addEdge(x, y, c, l);
    int64_t ans = dnc.minFlow(S, T);
    if (ans == -1) return cout << "please go home to sleep" << endl, void();
    cout << ans << endl;
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
