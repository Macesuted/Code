/**
 * @file 7541.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 505
#define endl '\n'

typedef pair<int, int> pii;

class Dinic {
   private:
    struct Edge {
        int to, cap, flow, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    queue<int> que;
    vector<bool> vis;
    vector<int> dist;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) cur[i] = graph[i].begin(), dist[i] = -1e9, vis[i] = false;
        que.push(S), dist[S] = 0, vis[S] = true;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = false;
            for (auto i : graph[p])
                if (i.cap > i.flow && dist[i.to] < dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) que.push(i.to), vis[i.to] = true;
                }
        }
        return dist[T] != -1e9;
    }
    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        vis[p] = true;
        int c, used = 0;
        for (auto i = cur[p]; rest && i != graph[p].end(); i++) {
            cur[p] = i;
            if (i->cap == i->flow || dist[i->to] != dist[p] + i->cost || vis[i->to]) continue;
            if (!(c = dfs(i->to, min(rest, i->cap - i->flow)))) dist[i->to] = -1;
            i->flow += c, graph[i->to][i->rev].flow -= c, used += c, rest -= c;
        }
        // vis[p] = false;
        return used;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), vis.resize(n + 1), dist.resize(n + 1); }
    void addEdge(int x, int y, int t, int w) {
        return graph[x].push_back(Edge{y, t, 0, w, (int)graph[y].size()}),
               graph[y].push_back(Edge{x, t, t, -w, (int)graph[x].size() - 1});
    }
    void solve(int _S, int _T, int n) {
        S = _S, T = _T;
        vector<int> answer;
        answer.resize(n + 1);
        for (int l = 1, r; l <= n; l = r + 1) {
            bfs();
            r = l + dfs(S, n) - 1;
            for (int i = l; i <= r; i++) answer[i] = answer[i - 1] + dist[T];
        }
        for (int i = 1; i <= n; i++) answer[i] = answer[n] - answer[i];
        for (int i = 1; i <= n; i++) cout << answer[i] << ' ';
        cout << endl;
        return;
    }
};

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    int S = 2 * n + 1, T = S + 1;
    Dinic dnc;
    dnc.resize(T);
    for (int i = 1; i <= n; i++) cin >> a[i], dnc.addEdge(S, i, 1, 0), dnc.addEdge(n + i, T, 1, 0);
    for (int i = 1, w; i <= n; i++) cin >> w, dnc.addEdge(i, n + i, 1, w);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[i] > a[j]) dnc.addEdge(n + i, j, 1, 0);
    dnc.solve(S, T, n);
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}