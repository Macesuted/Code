/**
 * @file 1452G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-10
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

#define maxn 200005

typedef pair<int, int> pii;

vector<int> graph[maxn];
int dist[maxn], siz[maxn], dep[maxn], f[maxn], ans[maxn];
bool vis[maxn];

int Max(int &a, int b) { return a = max(a, b); }

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !vis[i]) dfs1(i, p), siz[p] += siz[i];
    return;
}
pii dfs2(int p, int all, int pre = -1) {
    pii ans = {0x3f3f3f3f, p};
    dep[p] = 1;
    int maxSon = all - siz[p];
    for (auto i : graph[p])
        if (i != pre && !vis[i])
            ans = min(ans, dfs2(i, all, p)), maxSon = max(maxSon, siz[i]), dep[p] = max(dep[p], dep[i] + 1);
    return min(ans, pii{maxSon, p});
}
void dfs3(int p, int pre = -1) {
    dep[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !vis[i]) dfs3(i, p), dep[p] = max(dep[p], dep[i] + 1);
    return;
}
void dfs4(int p, int lim, int dep = 0, int pre = -1) {
    if (dist[p] - dep - 1 >= 0) Max(f[min(dist[p] - dep - 1, lim)], dist[p]);
    for (auto i : graph[p])
        if (i != pre && !vis[i]) dfs4(i, lim, dep + 1, p);
    return;
}
void dfs5(int p, int dep = 0, int pre = -1) {
    ans[p] = max(ans[p], f[dep]);
    for (auto i : graph[p])
        if (i != pre && !vis[i]) dfs5(i, dep + 1, p);
    return;
}
int findRoot(int p) { return dfs1(p), dfs2(p, siz[p]).second; }
void dfz(int p) {
    vis[p] = true, dfs3(p);
    for (int i = 0; i <= dep[p]; i++) f[i] = 0;
    if (dist[p]) Max(f[min(dist[p] - 1, dep[p])], dist[p]);
    dfs4(p, dep[p]);
    for (int i = dep[p] - 1; ~i; i--) f[i] = max(f[i], f[i + 1]);
    dfs5(p);
    for (auto i : graph[p])
        if (!vis[i]) dfz(findRoot(i));
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    int k;
    cin >> k;
    memset(dist, 0x3f, sizeof(dist));
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1, x; i <= k; i++) cin >> x, dist[x] = 0, que.push(x);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (dist[i] == 0x3f3f3f3f) dist[i] = dist[p] + 1, que.push(i);
    }
    dfz(findRoot(1));
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}