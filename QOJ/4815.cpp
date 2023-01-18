/**
 * @file 4815.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-18
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

#define maxn 40005
#define maxk 3005

int k, a[maxn], f[maxn][maxk], g[maxn][maxk], h[maxk], siz[maxn], ans[maxn];
vector<vector<int>> graph;

void dfs1(int p, int pre = -1) {
    siz[p] = 1, f[p][1] = a[p];
    for (auto i : graph[p]) {
        if (i == pre) continue;
        dfs1(i, p);
        for (int j = 1; j <= min(k, siz[p]); j++) h[j] = g[i][j] = f[p][j];
        for (int x = 1; x <= min(k, siz[p]); x++)
            for (int y = 1; y <= min(k - x, siz[i]); y++) f[p][x + y] = max(f[p][x + y], h[x] + f[i][y]);
        for (int j = 1; j <= min(k, siz[p]); j++) h[j] = 0;
        siz[p] += siz[i];
    }
    return;
}
void dfs2(int p, int pre = -1) {
    reverse(graph[p].begin(), graph[p].end());
    for (auto i : graph[p]) {
        if (i == pre) continue;
        siz[p] -= siz[i];
        for (int j = 1; j <= min(k, siz[p]); j++) h[j] = g[i][j], g[i][j] = 0;
        for (int x = 1; x <= min(k, siz[p]); x++)
            for (int y = 1; y <= min(k - x, siz[i]); y++) g[i][y] = max(g[i][y], h[x] + g[p][x + y]);
        for (int j = 1; j <= min(k, siz[p] + siz[i]); j++) h[j] = g[p][j];
        for (int x = 1; x <= min(k, siz[p]); x++)
            for (int y = 1; y <= min(k - x, siz[i]); y++) g[p][x] = max(g[p][x], f[i][y] + h[x + y]);
        for (int j = 1; j <= min(k, siz[p] + siz[i]); j++) h[j] = 0;
        dfs2(i, p);
    }
    ans[p] = f[p][1] + g[p][1];
    return;
}

void solve(void) {
    int n;
    cin >> n >> k, graph.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1), dfs2(1);
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