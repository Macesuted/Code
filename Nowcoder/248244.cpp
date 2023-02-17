/**
 * @file 248244.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-16
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

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

vector<vector<pii>> graph;
vector<tiii> edges;
bool vis[maxn], g[maxn];
int dep[maxn];
int64_t a[maxn], f[maxn][2];

void dfs(int p, int pre = -1) {
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i.first])
            dep[i.first] = dep[p] + 1, f[i.first][0] = f[p][1], f[i.first][1] = f[p][0] + i.second, dfs(i.first, p);
        else if (i.first != pre)
            edges.emplace_back(p, i.first, i.second);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m, graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);
    for (int i = 1; i <= n; i++) vis[i] = g[i] = false, a[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        edges.clear();
        f[i][0] = f[i][1] = dep[i] = 0, dfs(i);
        bool chk = false;
        for (auto i : edges) {
            int x, y, w;
            tie(x, y, w) = i;
            if (dep[x] > dep[y]) swap(x, y);
            int64_t v = f[y][0] + f[y][1] - f[x][0] - f[x][1] + w;
            if (v & 1) return cout << -1 << endl, void();
            v /= 2;
            if ((dep[y] - dep[x] + 1) & 1) {
                int64_t w = v - f[y][0] + f[x][0];
                if (a[y] && a[y] != w) return cout << -1 << endl, void();
                a[y] = w, chk = g[y] = true;
            } else if (v != f[y][1] - f[x][0])
                return cout << -1 << endl, void();
        }
        if (!chk) g[i] = true;
    }
    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (g[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p]) {
            int v = i.second - a[p];
            if (!g[i.first])
                a[i.first] = v, g[i.first] = true, que.push(i.first);
            else if (a[i.first] != v)
                return cout << -1 << endl, void();
        }
    }
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}