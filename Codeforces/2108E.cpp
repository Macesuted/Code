/**
 * @file 2108E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-07
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

using pii = pair<int, int>;

vector<vector<int>> graph;
int col[maxn], fa[maxn], dep[maxn], siz[maxn], dfn[maxn], id[maxn];
int n;

int dfnt;
void dfs(int p) {
    id[dfn[p] = ++dfnt] = p, siz[p] = 1;
    for (auto q : graph[p]) {
        if (q == fa[p]) continue;
        fa[q] = p, dep[q] = dep[p] + 1;
        dfs(q);
        siz[p] += siz[q];
    }
    return;
}
int getRoot(int p) {
    for (auto q : graph[p])
        if (q != fa[p] && 2 * siz[q] > n) return getRoot(q);
    return p;
}

void solve(void) {
    cin >> n;

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    fa[1] = -1, dep[1] = 0, dfnt = 0, dfs(1);
    int root = getRoot(1);
    fa[root] = -1, dep[root] = 0, dfnt = 0, dfs(root);

    int x = -1;
    for (int i = 1; i <= n; i++)
        if (i != root && (x == -1 || siz[i] + dep[i] < siz[x] + dep[x])) x = i;

    cout << x << ' ' << fa[x] << endl;

    for (int i = 1; i <= n; i++) col[i] = 0;
    vector<int> nodes;
    for (int i = 1; i <= n; i++)
        if (id[i] != x) nodes.push_back(id[i]);
    for (int i = 0, j = nodes.size() / 2; j < (int)nodes.size(); i++, j++) col[nodes[i]] = col[nodes[j]] = i + 1;
    if (x < fa[x]) swap(col[x], col[fa[x]]);

    for (int i = 1; i <= n; i++) cout << col[i] << ' ';
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