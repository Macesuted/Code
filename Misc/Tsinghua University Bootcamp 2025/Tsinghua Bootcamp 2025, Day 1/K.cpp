/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2505

class Dinic {
   private:
    struct Edge {
        int to, cap, rev;
    };

    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 0; i < n; i++) cur[i] = graph[i].begin(), dist[i] = INT_MAX;
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
        if (p == T) return rest;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, use += c, rest -= c;
        }
        return use;
    }

   public:
    vector<vector<Edge>> graph;

    void resize(int _n) { return graph.resize(n = _n), cur.resize(n), dist.resize(n); }
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

int ans[maxn];
bool f[maxn][26], mark[maxn];
vector<int> graph[maxn];
string s;

void dfs(int p) {
    mark[p] = true;
    for (auto q : graph[p]) dfs(q);
    return;
}

void solve(void) {
    cin >> s;
    int n = s.size();
    s = ' ' + s;

    stack<int> S;
    for (int i = 1; i <= n; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            S.push(i);
            continue;
        }
        graph[i].push_back(S.top()), S.pop();
        graph[i].push_back(S.top()), S.pop();
        S.push(i);
    }

    for (int i = 1; i <= n; i++) {
        vector<int> cur = graph[i];
        graph[i].clear();
        for (auto p : cur)
            if (s[p] != s[i])
                graph[i].push_back(p);
            else
                for (auto q : graph[p]) graph[i].push_back(q);
    }

    dfs(n);

    for (int i = 1; i <= n; i++) {
        if (!mark[i]) continue;

        ans[i] = 1;
        if ('a' <= s[i] && s[i] <= 'z') continue;

        vector<int> cur;
        array<int, 26> ch;
        for (int i = 0; i < 26; i++) ch[i] = 0;
        for (auto p : graph[i]) {
            ans[i] += ans[p];
            if ('a' <= s[p] && s[p] <= 'z')
                ch[s[p] - 'a']++;
            else
                cur.push_back(p);
        }

        Dinic dnc;
        int m = cur.size(), S = m + 26, T = S + 1;
        dnc.resize(T + 1);
        for (int i = 0; i < m; i++) {
            dnc.addEdge(S, i, 1);
            for (int t = 0; t < 26; t++)
                if (f[cur[i]][t]) dnc.addEdge(i, m + t, 1);
        }
        for (int t = 0; t < 26; t++)
            if (ch[t]) dnc.addEdge(m + t, T, 1), ans[i] -= ch[t] - 1;

        ans[i] -= dnc.maxFlow(S, T);

        for (int t = 0; t < 26; t++) {
            if (ch[t]) {
                f[i][t] = true;
                continue;
            }

            Dinic cnc = dnc;
            cnc.addEdge(cur.size() + t, T, 1);
            int ret = cnc.maxFlow(S, T);
            assert(ret == 0 || ret == 1);
            f[i][t] = ret;
        }
    }

    cout << ans[n] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
