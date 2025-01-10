/**
 * @file 105631D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
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

#define maxn 200005

vector<int> graph[maxn];
int64_t f[maxn], g[maxn], siz[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = 1, f[p] = 0;
    for (auto q : graph[p])
        if (q != pre) dfs1(q, p), f[p] += f[q] + siz[q] * (siz[q] - 1), siz[p] += siz[q];
    return;
}

void dfs2(int p, int pre = -1) {
    g[p] = f[p];
    for (auto q : graph[p]) {
        if (q == pre) continue;
        f[p] -= f[q] + siz[q] * (siz[q] - 1), siz[p] -= siz[q];
        f[q] += f[p] + siz[p] * (siz[p] - 1), siz[q] += siz[p];
        dfs2(q, p);
        f[q] -= f[p] + siz[p] * (siz[p] - 1), siz[q] -= siz[p];
        f[p] += f[q] + siz[q] * (siz[q] - 1), siz[p] += siz[q];
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs1(1);

    dfs2(1);

    for (int i = 1; i <= n; i++) cout << g[i] / 2 << endl;

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