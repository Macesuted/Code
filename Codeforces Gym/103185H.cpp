/**
 * @file 103185H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Dinic {
   private:
    struct Edge {
        int to, cap, rev;
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
        return dist[T] != INT_MAX;
    }
    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        int used = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, used += c, rest -= c;
        }
        return used;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1});
    }
    int maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int ans = 0;
        while (bfs()) ans += dfs(S, INT_MAX);
        return ans;
    }
};

void solve(void) {
    int n;
    cin >> n;
    int S = n + 1, T = n + 2;
    Dinic dnc;
    dnc.resize(T);
    for (int i = 1; i <= n; i++) {
        string op;
        cin >> op;
        if (op == "*") {
            int v;
            cin >> v;
            int x = i, y = v;
            if (x == 1) x = S;
            if (y == 1) y = T;
            dnc.addEdge(x, y, 1e8);
        } else {
            int m = stoi(op);
            for (int j = 0, t; j < m; j++) {
                cin >> t;
                int x = i, y = t;
                if (x == 1) x = S;
                if (y == 1) y = T;
                dnc.addEdge(x, y, 1);
            }
        }
    }
    int ans = dnc.maxFlow(S, T);
    if (ans >= 1e8) return cout << '*' << endl, void();
    cout << ans + 1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}