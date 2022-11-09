/**
 * @file 110.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

vector<pii> graph[maxn << 1];
int n, k, maxd, siz[maxn << 1], rec[maxn << 1], f[maxn << 1], g[maxn << 1];
bool vis[maxn << 1];

void dfs1(int p, int fa = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != fa && !vis[i.first]) dfs1(i.first, p), siz[p] += siz[i.first];
    return;
}
pii dfs2(int p, int tot, int fa = -1) {
    pii ans = {INT_MAX, 0};
    int maxv = tot - siz[p];
    for (auto i : graph[p])
        if (i.first != fa && !vis[i.first]) ans = min(ans, dfs2(i.first, tot, p)), maxv = max(maxv, siz[i.first]);
    return min(ans, pii{maxv, p});
}
int dfs3(int p, int dep = 0, int fa = -1) {
    rec[dep] += (p <= n);
    int maxd = dep;
    for (auto i : graph[p])
        if (i.first != fa && !vis[i.first]) maxd = max(maxd, dfs3(i.first, dep + 1, p));
    return maxd;
}
void dfs4(int p, int op, int dep = 0, int edg = -1, int fa = -1) {
    if (k - dep < 0) return;
    f[p] += op * rec[min(maxd, k - dep)];
    if (~edg) g[edg] += op * rec[min(maxd, k - dep)];
    for (auto i : graph[p])
        if (i.first != fa && !vis[i.first])
            dfs4(i.first, op, dep + 1, i.second, p);
        else if (i.first != fa)
            g[i.second] += op * rec[min(maxd, k - dep - 1)];
    return;
}
void solve(int p) {
    dfs1(p), p = dfs2(p, siz[p]).second, vis[p] = true;
    maxd = dfs3(p);
    for (int i = 1; i <= maxd; i++) rec[i] += rec[i - 1];
    dfs4(p, +1);
    for (int i = 0; i <= maxd; i++) rec[i] = 0;
    for (auto i : graph[p])
        if (!vis[i.first]) {
            maxd = dfs3(i.first, 1, p);
            for (int i = 1; i <= maxd; i++) rec[i] += rec[i - 1];
            dfs4(i.first, -1, 1, i.second, p);
            for (int i = 0; i <= maxd; i++) rec[i] = 0;
        }
    for (auto i : graph[p])
        if (!vis[i.first]) solve(i.first);
    return;
}

void solve(void) {
    cin >> n >> k;
    auto addEdge = [&](int x, int y, int id) { return graph[x].emplace_back(y, id), graph[y].emplace_back(x, id); };
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, addEdge(x, n + i, i), addEdge(y, n + i, n - 1 + i);
    solve(1);
    int64_t ans = 0;
    for (int i = 1; i < 2 * n; i++) ans += (int64_t)f[i] * (f[i] - 1) * (f[i] - 2) / 6;
    for (int i = 1; i < 2 * n - 1; i++) ans -= (int64_t)g[i] * (g[i] - 1) * (g[i] - 2) / 6;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
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