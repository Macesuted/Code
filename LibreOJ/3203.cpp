/**
 * @file 3203.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
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

#define maxn 100005
#define maxlgn 20

typedef pair<int, int> pii;

pii edg[maxn];
bool mark[maxn];
int siz[maxn], son[maxn], top[maxn], fa[maxn], dfni[maxn], dfno[maxn], lg2[maxn];
int64_t dep[maxn], f[maxn], ST[maxn][maxlgn];
vector<vector<pii>> graph;

void dfs1(int p, int pre = -1) {
    f[p] = (mark[p] ? dep[p] : 1e18), siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != pre) {
            dep[i.first] = dep[p] + i.second, fa[i.first] = p;
            dfs1(i.first, p);
            f[p] = min(f[p], f[i.first]), siz[p] += siz[i.first];
            if (!son[p] || siz[i.first] > siz[son[p]]) son[p] = i.first;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int _top) {
    dfni[p] = ++dfnt, top[p] = _top;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i.first != fa[p] && i.first != son[p]) dfs2(i.first, i.first);
    dfno[p] = dfnt;
    return;
}
int64_t query(int l, int r) {
    int lgLen = lg2[r - l + 1];
    return min(ST[l][lgLen], ST[r - (1 << lgLen) + 1][lgLen]);
}

void solve(void) {
    int n, m, q, root;
    cin >> n >> m >> q >> root, graph.resize(n + 1);
    for (int i = 1, x, y, t; i < n; i++)
        cin >> x >> y >> t, graph[x].emplace_back(y, t), graph[y].emplace_back(x, t), edg[i] = {x, y};
    for (int i = 1, p; i <= m; i++) cin >> p, mark[p] = true;
    dfs1(root), dfs2(root, root);
    for (int i = 1; i <= n; i++) ST[dfni[i]][0] = (f[i] == 1e18 ? 1e18 : f[i] - 2 * dep[i]), assert(f[i] >= dep[i]);
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) ST[j][i] = min(ST[j][i - 1], ST[j + (1 << (i - 1))][i - 1]);
    while (q--) {
        int e, x, p;
        cin >> e >> x, p = (dep[edg[e].first] > dep[edg[e].second] ? edg[e].first : edg[e].second);
        int64_t rec = dep[x];
        if (!(dfni[p] <= dfni[x] && dfni[x] <= dfno[p])) {
            cout << "escaped" << endl;
            continue;
        }
        int64_t v = 1e18;
        while (top[p] != top[x]) v = min(v, query(dfni[top[x]], dfni[x])), x = fa[top[x]];
        v = min(v, query(dfni[p], dfni[x]));
        if (v == 1e18)
            cout << "oo" << endl;
        else
            cout << v + rec << endl;
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}