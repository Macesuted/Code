# Graph

## Dinic

```cpp
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
    void resize(int _n) {
        return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1);
    }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1});
    }
    int64_t maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int64_t ans = 0;
        while (bfs()) ans += dfs(S, INT64_MAX);
        return ans;
    }
};
```

## Dinic with Cost

```cpp
class DinicWithCost {
   private:
    struct Edge {
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = INT_MAX, vis[i] = false, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop(), vis[p] = false;
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) vis[i.to] = true, que.push(i.to);
                }
        }
        return dist[T] != INT_MAX;
    }
    int dfs(int p, int rest) {
        if (p == T) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + i->cost || vis[i->to]) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = -1;
            i->cap -= c, graph[i->to][i->rev].cap += c, use += c, rest -= c;
        }
        vis[p] = false;
        return use;
    }

   public:
    void resize(int _n) {
        return graph.resize((n = _n) + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1);
    }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    pair<int, int> maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int flow = 0, cost = 0;
        while (bfs()) {
            int c = dfs(S, INT_MAX);
            flow += c, cost += dist[T] * c;
        }
        return {flow, cost};
    }
};
```

## Dinic with Lowerbound

```cpp
class DinicWithLowerbound {
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
    void resize(int _n) {
        return graph.resize((n = _n + 2) + 1), cur.resize(n + 1),
               dist.resize(n + 1), preF.resize(n + 1);
    }
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
```