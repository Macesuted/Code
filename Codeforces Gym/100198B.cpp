/**
 * @file 100198B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-11
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
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    int dfs(int p, int rest) {
        if (p == T) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || vis[i->to]) continue;
            c = dfs(i->to, min(rest, i->cap));
            i->cap -= c, graph[i->to][i->rev].cap += c, use += c, rest -= c;
        }
        vis[p] = false;
        return use;
    }

   public:
    void resize(int _n) { return graph.resize((n = _n) + 1), cur.resize(n + 1), vis.resize(n + 1); }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    void maxFlow(int _S, int _T) {
        S = _S, T = _T;

        sort(graph[S].begin(), graph[S].end(), [](const Edge& a, const Edge& b) { return a.cost > b.cost; });

        vis[S] = true;
        for (auto& e : graph[S]) {
            for (int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            if (dfs(e.to, 1)) e.cap = 0, graph[e.to][e.rev].cap = 1;
        }

        return;
    }
    vector<int> getAns(int n) {
        vector<int> ans(n + 1);
        for (int i = 1; i <= n; i++)
            for (auto e : graph[i])
                if (e.to != S && !e.cap) ans[i] = e.to - n;
        return ans;
    }
};

void solve(void) {
    int n;
    cin >> n;

    int S = 2 * n + 1, T = 2 * n + 2;
    Dinic dnc;
    dnc.resize(T);

    for (int i = 1, v; i <= n; i++) cin >> v, dnc.addEdge(S, i, 1, v * v), dnc.addEdge(n + i, T, 1, 0);

    for (int i = 1, s, x; i <= n; i++) {
        cin >> s;
        while (s--) cin >> x, dnc.addEdge(i, n + x, 1, 0);
    }

    dnc.maxFlow(S, T);

    auto ret = dnc.getAns(n);

    for (int i = 1; i <= n; i++) cout << ret[i] << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("beloved.in", "r", stdin), freopen("beloved.out", "w", stdout);
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