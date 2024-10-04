#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

typedef pair<int, int> pii;

class Dinic {
   private:
    struct Edge {
        int to, cap, rev, id;
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
                if (dist[i.to] > dist[p] + 1 && i.cap) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T] != INT_MAX;
    }
    int dfs(int p, int rest) {
        if (p == T) return rest;
        int used = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap)))) dist[i->to] = -1;
            used += c, rest -= c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        return used;
    }

   public:
    vector<bool> avai;
    set<int> edges[2];

    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), avai.resize(n + 1); }
    void addEdge(int from, int to, int cap, int id) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size(), id}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1, 0});
    }
    int solve(int _S, int _T) {
        S = _S, T = _T;
        int flow = 0;
        while (bfs()) flow += dfs(S, INT_MAX);
        for (int i = 1; i <= n; i++)
            for (auto j : graph[i])
                if (j.id) edges[!j.cap].insert(j.id);
        return flow;
    }
};

map<int, set<pii>> R, C;
int nx[maxn], ny[maxn];
bool vis[maxn];
vector<int> rec[maxn];

void solve(void) {
    R.clear(), C.clear();

    int n, m, k;
    cin >> n >> m >> k;

    Dinic dnc;
    int S = 2 * n + 1, T = S + 1;
    dnc.resize(T);

    for (int i = 1, x, y; i <= n; i++)
        cin >> x >> y, R[x].emplace(y, i), C[y].emplace(x, i), dnc.addEdge(S, i, 1, 0), dnc.addEdge(n + i, T, 1, 0);
    for (int i = 1; i <= 2 * n; i++) rec[i].clear(), vis[i] = false;
    int ans = 0;
    for (auto &i : R) ans += (int)i.second.size() - 1;
    for (auto &i : C) ans += (int)i.second.size() - 1;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y, nx[i] = -1, ny[i] = -1;
        if (R.count(x)) {
            auto p = R[x].lower_bound({y, 0});
            if (p != R[x].begin() && p != R[x].end()) dnc.avai[nx[i] = p->second] = true;
        }
        if (C.count(y)) {
            auto p = C[y].lower_bound({x, 0});
            if (p != C[y].begin() && p != C[y].end()) dnc.avai[ny[i] = n + p->second] = true;
        }
        if (nx[i] != -1 && ny[i] != -1) dnc.addEdge(nx[i], ny[i], 1, i);
    }
    // cerr << "! " << ans << endl;
    int cnt = m - k, flow = dnc.solve(S, T);
    if (flow >= cnt) {
        cout << ans - cnt * 2 << endl;
        for (int i = 1; i <= m; i++)
            if (!dnc.edges[1].count(i) || !cnt)
                cout << i << ' ';
            else
                cnt--;
        cout << endl;
        return;
    }
    cnt -= flow, ans -= flow * 2;
    for (int i = 1; i <= m; i++)
        if (!dnc.edges[1].count(i)) {
            if (nx[i] != -1) rec[nx[i]].push_back(i);
            if (ny[i] != -1) rec[ny[i]].push_back(i);
        } else
            vis[nx[i]] = vis[ny[i]] = true;
    // cerr << "# " << cnt << endl;
    for (int i = 1; i <= m; i++) {
        if (dnc.edges[1].count(i)) continue;
        if (nx[i] != -1 && !vis[nx[i]] && cnt) vis[nx[i]] = true, dnc.edges[1].insert(i), ans--, cnt--;
        if (ny[i] != -1 && !vis[ny[i]] && cnt) vis[ny[i]] = true, dnc.edges[1].insert(i), ans--, cnt--;
    }
    // cerr << "# " << cnt << endl;
    for (int i = 1; i <= m; i++)
        if (!dnc.edges[1].count(i) && cnt) dnc.edges[1].insert(i), cnt--;

    // cerr << "###" << endl;
    cout << ans << endl;
    for (int i = 1; i <= m; i++)
        if (!dnc.edges[1].count(i)) cout << i << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}