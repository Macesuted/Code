/**
 * @file 1761G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 75005

typedef pair<int, int> pii;

mt19937 rnd(114514);
vector<int> a, s, v, siz, dep;
vector<vector<int>> dist, son, graph;
bool vis[maxn * 2];
int tn;

int ask(int x, int y) {
    cout << "? " << x + 1 << ' ' << y + 1 << endl;
    int t;
    cin >> t;
    return t;
}

void dfs(int p) {
    if (son[p].empty()) return;
    map<int, int> rec;
    vector<int> sons = son[p];
    son[p].clear();
    int q = sons.front();
    for (int i = 1; i < (int)sons.size(); i++)
        if (dep[sons[i]] > dep[q]) q = sons[i];
    rec[dep[p]] = p, rec[dep[q]] = q;
    for (int i = 0; i < (int)sons.size(); i++)
        if (i != q && dep[sons[i]] + dist[sons[i]][q] == dep[q]) rec[dist[a[0]][sons[i]]] = sons[i];
    for (int i = 0; i < (int)sons.size(); i++)
        if (i != q && dep[sons[i]] + dist[sons[i]][q] != dep[q]) {
            int d = (dep[sons[i]] - dist[sons[i]][q] + dep[q]) / 2;
            if (!rec.count(d)) dep[rec[d] = ++tn] = d;
            son[rec[d]].push_back(sons[i]);
        }
    for (auto x = rec.begin(), y = ++rec.begin(); y != rec.end(); x++, y++)
        graph[x->second].push_back(y->second), graph[y->second].push_back(x->second);
    for (auto i : rec) dfs(i.second);
    return;
}
void dfs1(int p, int pre = -1) {
    siz[p] = vis[p];
    for (auto i : graph[p])
        if (i != pre) dfs1(i, p), siz[p] += siz[i];
    return;
}
pii dfs2(int p, int tot, int pre = -1) {
    pii ans = {INT_MAX, 0};
    int maxs = tot - siz[p];
    for (auto i : graph[p])
        if (i != pre) ans = min(ans, dfs2(i, tot, p)), maxs = max(maxs, siz[i]);
    return min(ans, pii{maxs, p});
}
int dfs3(int p, int pre = -1) {
    int x = -1;
    for (auto i : graph[p])
        if (i != pre && (!~x || siz[i] > siz[x])) x = i;
    return ~x ? dfs3(x, p) : p;
}

void solve(void) {
    int n, m;
    cin >> n, m = min(n, 316);
    a.resize(m), dist.resize(n), son.resize(n * 2), graph.resize(n * 2), siz.resize(n * 2), dep.resize(n * 2), tn = n - 1;
    for (int i = 0; i < m; i++) {
        a[i] = rnd() % n;
        while (vis[a[i]]) a[i] = rnd() % n;
        vis[a[i]] = true;
    }
    for (int i = 0; i < m; i++) dist[a[i]].resize(n);
    for (int i = 0; i < m; i++) {
        dist[a[i]][a[i]] = 0;
        for (int j = i + 1; j < m; j++) dist[a[i]][a[j]] = dist[a[j]][a[i]] = ask(a[i], a[j]);
    }
    for (int i = 1; i < m; i++) son[a[0]].push_back(a[i]);
    for (int i = 0; i < m; i++) dep[a[i]] = dist[a[0]][a[i]];
    dfs(a[0]), dfs1(a[0]);
    int root = dfs2(a[0], m).second;
    dfs1(root);
    sort(graph[root].begin(), graph[root].end(), [&](int x, int y) { return siz[x] > siz[y]; });
    int x = dfs3(graph[root][0], root), y = dfs3(graph[root][1], root), len = dist[x][y];
    s.resize(len + 1), v.resize(len + 1);
    for (int i = 0; i < n; i++) {
        int dx = ask(x, i), dy = ask(y, i);
        s[(dx - dy + len) / 2]++;
        if (dx + dy == len) v[dx] = i;
    }
    int sum = s[0], p = 0;
    while (sum <= n - sum) sum += s[++p];
    cout << "! " << v[p] + 1 << endl;
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