/**
 * @file 12727.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

#ifdef LOCAL

bool mem1;

#endif

class FoxAndCity {
   private:
    class Dinic {
       private:
        struct Edge {
            int to, cap, flow, rev;
        };
        vector<vector<Edge>> graph;
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
                    if (i.cap > i.flow && dist[i.to] == 0) que.push(i.to), dist[i.to] = dist[p] + 1;
            }
            return dist[T];
        }
        int dfs(int p, int rest) {
            if (p == T || !rest) return rest;
            int use = 0, c;
            for (auto i = cur[p]; i != graph[p].end(); i++) {
                cur[p] = i;
                if (i->cap == i->flow || dist[i->to] != dist[p] + 1) continue;
                if ((c = dfs(i->to, min(rest - use, i->cap - i->flow))) == 0) dist[i->to] = 0;
                use += c, i->flow += c, graph[i->to][i->rev].flow -= c;
            }
            return use;
        }

       public:
        void resize(int _n) { return n = _n, graph.resize(n + 1), dist.resize(n + 1), cur.resize(n + 1); }
        void addEdge(int from, int to, int cap) {
            return graph[from].push_back({to, cap, 0, (int)graph[to].size()}),
                   graph[to].push_back({from, cap, cap, (int)graph[from].size() - 1});
        }
        int maxFlow(int _S, int _T) {
            S = _S, T = _T;
            int ans = 0;
            while (bfs()) ans += dfs(S, numeric_limits<int>::max());
            return ans;
        }
    } net;

    const int INF = numeric_limits<int>::max();

   public:
    int minimalCost(vector<string> linked, vector<int> want) {
        int n = linked.size(), S = n * (n + 2) + 1, T = S + 1;
        net.resize(T);
        net.addEdge(S, 1, INF), net.addEdge(1, 2, want[0] * want[0]);
        for (int j = 2; j <= n + 1; j++) net.addEdge(j, j + 1, INF);
        net.addEdge(n + 2, T, INF);
        for (int i = 2; i <= n; i++) {
            net.addEdge(S, (i - 1) * (n + 2) + 1, INF), net.addEdge((i - 1) * (n + 2) + 1, (i - 1) * (n + 2) + 2, INF);
            for (int j = 2; j <= n + 1; j++)
                net.addEdge((i - 1) * (n + 2) + j, (i - 1) * (n + 2) + j + 1,
                            abs(want[i - 1] - j + 1) * abs(want[i - 1] - j + 1));
            net.addEdge(i * (n + 2), T, INF);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (linked[i - 1][j - 1] == 'Y')
                    for (int k = 1; k <= n; k++) net.addEdge((j - 1) * (n + 2) + k + 1, (i - 1) * (n + 2) + k, INF);
        return net.maxFlow(S, T);
    }
};

#ifdef LOCAL

FoxAndCity _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    vector<string> linked;
    vector<int> want;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        linked.push_back(s);
    }
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        want.push_back(t);
    }
    cout << _.minimalCost(linked, want) << endl;

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif