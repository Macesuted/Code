/**
 * @file 101808K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

#define maxn 100005
#define maxlgn 20

using pii = pair<int, int>;

vector<vector<pii>> graph;
vector<int> ring;
vector<bool> vis;
int fa[maxn][maxlgn], bel[maxn], dep[maxn], id[maxn];
int64_t dist[maxn][maxlgn];

vector<int> S;
void dfs1(int p, int pre = -1) {
    if (vis[p]) {
        ring.push_back(p);
        for (auto x = S.rbegin(); *x != p; x++) ring.push_back(*x);
        return;
    }
    vis[p] = true, S.push_back(p);
    for (auto [q, w] : graph[p])
        if (q != pre && ring.empty()) dfs1(q, p);
    S.pop_back();
    return;
}
void dfs2(int p, int pre) {
    for (auto [q, w] : graph[p])
        if (q != pre) bel[q] = bel[p], dep[q] = dep[p] + 1, fa[q][0] = p, dist[q][0] = w, dfs2(q, p);
    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y, w; i <= n; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);

    ring.clear(), vis.clear(), vis.resize(n + 1, false), dfs1(1);
    vis.clear(), vis.resize(n + 1, false);
    for (auto x : ring) vis[x] = true, fa[x][0] = x, dist[x][0] = 0, bel[x] = x, dep[x] = 0;
    for (auto x : ring)
        for (auto [y, w] : graph[x])
            if (!vis[y]) fa[y][0] = x, dist[y][0] = w, bel[y] = x, dep[y] = 1, dfs2(y, x);
    for (int t = 1; t < maxlgn; t++)
        for (int i = 1; i <= n; i++)
            fa[i][t] = fa[fa[i][t - 1]][t - 1], dist[i][t] = dist[i][t - 1] + dist[fa[i][t - 1]][t - 1];

    int m = ring.size();
    vector<int64_t> ringDist(m + 1);
    for (int i = 0; i < m; i++)
        for (auto [p, w] : graph[ring[i]])
            if (p == ring[(i + 1) % m]) ringDist[i + 1] = w;
    for (int i = 1; i <= m; i++) ringDist[i] += ringDist[i - 1];
    for (int i = 0; i < m; i++) id[ring[i]] = i + 1;

    while (q--) {
        int x, y;
        cin >> x >> y;
        if (bel[x] == bel[y]) {
            int64_t ans = 0;
            if (dep[x] < dep[y]) swap(x, y);
            for (int t = maxlgn - 1; ~t; t--)
                if (dep[fa[x][t]] >= dep[y]) ans += dist[x][t], x = fa[x][t];
            if (x != y) {
                for (int t = maxlgn - 1; ~t; t--)
                    if (fa[x][t] != fa[y][t]) ans += dist[x][t] + dist[y][t], x = fa[x][t], y = fa[y][t];
                ans += dist[x][0] + dist[y][0];
            }
            cout << ans << endl;
            continue;
        }
        int64_t ans = dist[x][maxlgn - 1] + dist[y][maxlgn - 1];
        x = id[bel[x]], y = id[bel[y]];
        if (x > y) swap(x, y);
        ans += min(ringDist[y - 1] - ringDist[x - 1], ringDist[m] - ringDist[y - 1] + ringDist[x - 1]);
        cout << ans << endl;
    }

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