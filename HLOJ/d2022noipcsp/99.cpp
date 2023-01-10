/**
 * @file 99.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 255

class Dinic {
   private:
    struct Edge {
        int to, cap, flow, rev;
    };

    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = 0, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap > i.flow && !dist[i.to]) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T];
    }
    int dfs(int p, int rest) {
        if (p == T) return rest;
        int flow = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (dist[i->to] != dist[p] + 1 || i->cap == i->flow) continue;
            if (!(c = dfs(i->to, min(rest, i->cap - i->flow)))) dist[i->to] = -1;
            flow += c, rest -= c, i->flow += c, graph[i->to][i->rev].flow -= c;
        }
        return flow;
    }

   public:
    vector<bool> vis;
    vector<vector<Edge>> graph;

    void resize(int _n) { return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back({to, cap, 0, (int)graph[to].size()}),
               graph[to].push_back({from, cap, cap, (int)graph[from].size() - 1});
    }
    int maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int ans = 0;
        while (bfs()) ans += dfs(S, INT_MAX);
        return ans;
    }
    void dfs(int p) {
        vis[p] = true;
        for (auto i : graph[p])
            if (i.cap > i.flow && !vis[i.to]) dfs(i.to);
        return;
    }
} net;

string a[maxn], b[maxn];

int cnt(int x, int y) { return int(a[x][y - 1] == '|') + (a[x][y] == '|') + (b[x - 1][y] == '-') + (b[x][y] == '-'); }

void solve(void) {
    int n, m;
    char typ;
    cin >> n >> m >> typ;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = "|" + a[i] + "|";
    b[0] = b[n] = string(m + 1, '-');
    for (int i = 1; i < n; i++) cin >> b[i], b[i] = " " + b[i];
    auto _ = [&](int x, int y) { return (x - 1) * m + y; };
    if (typ == 'L') {
        int s = n * m, S = 2 * s + 1, T = S + 1;
        net.resize(T);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < m; j++) {
                if (a[i][j] == '|') continue;
                net.addEdge(S, _(i, j), 1);
                if (b[i - 1][j] != '-') net.addEdge(_(i, j), s + _(i - 1, j), 1);
                if (b[i - 1][j + 1] != '-') net.addEdge(_(i, j), s + _(i - 1, j + 1), 1);
                if (b[i][j] != '-') net.addEdge(_(i, j), s + _(i, j), 1);
                if (b[i][j + 1] != '-') net.addEdge(_(i, j), s + _(i, j + 1), 1);
            }
        for (int i = 1; i < n; i++)
            for (int j = 1; j <= m; j++)
                if (b[i][j] != '-') net.addEdge(s + _(i, j), T, 1);
        cout << net.maxFlow(S, T) << endl;
        for (int i = 1; i <= T; i++) net.vis[i] = false;
        net.dfs(S);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < m; j++)
                if (!net.vis[_(i, j)]) a[i][j] = '|';
        for (int i = 1; i < n; i++)
            for (int j = 1; j <= m; j++)
                if (net.vis[s + _(i, j)]) b[i][j] = '-';
    } else {
        int S = n * m + 1, T = S + 1;
        net.resize(T);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (cnt(i, j) >= 2) continue;
                if ((i + j) & 1) {
                    net.addEdge(S, _(i, j), 2 - cnt(i, j));
                    if (a[i][j - 1] != '|') net.addEdge(_(i, j), _(i, j - 1), 1);
                    if (a[i][j] != '|') net.addEdge(_(i, j), _(i, j + 1), 1);
                    if (b[i - 1][j] != '-') net.addEdge(_(i, j), _(i - 1, j), 1);
                    if (b[i][j] != '-') net.addEdge(_(i, j), _(i + 1, j), 1);
                } else
                    net.addEdge(_(i, j), T, 2 - cnt(i, j));
            }
        int ret = net.maxFlow(S, T);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (!((i + j) & 1)) continue;
                for (auto e : net.graph[_(i, j)])
                    if (e.cap == e.flow && e.to != S) {
                        int x = (e.to - 1) / m + 1, y = (e.to - 1) % m + 1;
                        if (y == j - 1) a[i][j - 1] = '|';
                        if (y == j + 1) a[i][j] = '|';
                        if (x == i - 1) b[i - 1][j] = '-';
                        if (x == i + 1) b[i][j] = '-';
                    }
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (cnt(i, j) < 2 && a[i][j - 1] != '|') a[i][j - 1] = '|', ret++;
                if (cnt(i, j) < 2 && a[i][j] != '|') a[i][j] = '|', ret++;
                if (cnt(i, j) < 2 && b[i - 1][j] != '-') b[i - 1][j] = '-', ret++;
                if (cnt(i, j) < 2 && b[i][j] != '-') b[i][j] = '-', ret++;
                if (cnt(i, j) < 2) cerr << i << ' ' << j << endl;
            }
        cout << ret << endl;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) cout << a[i][j];
        cout << endl;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) cout << b[i][j];
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("walls.in", "r", stdin), freopen("walls.out", "w", stdout);
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