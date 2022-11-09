/**
 * @file 3952.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 305
#define BASE (maxn * maxn)

vector<int> graph[BASE * 2], tree[maxn];
int fa[maxn], dfni[maxn], dfno[maxn], dep[maxn], dfn[BASE * 2], low[BASE * 2], scc[BASE * 2];

int dfnt = 0;
void dfs(int p) {
    dfni[p] = ++dfnt;
    for (auto i : tree[p]) dep[i] = dep[p] + 1, dfs(i);
    dfno[p] = dfnt;
    return;
}
int tim = 0, cnt = 0;
stack<int> S;
void tarjan(int p) {
    dfn[p] = low[p] = ++tim;
    S.push(p);
    for (auto i : graph[p])
        if (!dfn[i])
            tarjan(i), low[p] = min(low[p], low[i]);
        else if (!~scc[i])
            low[p] = min(low[p], dfn[i]);
    if (dfn[p] == low[p]) {
        while (S.top() != p) scc[S.top()] = cnt, S.pop();
        scc[p] = cnt++, S.pop();
    }
    return;
}

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q;
    fa[0] = -1;
    for (int i = 1; i < n; i++) cin >> fa[i], tree[fa[i]].push_back(i);
    auto _ = [&](int x, int y, bool t) { return x * maxn + y + 1 + t * BASE; };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (~fa[i]) graph[_(i, j, 1)].push_back(_(fa[i], j, 1));
            for (auto x : tree[i]) graph[_(i, j, 0)].push_back(_(x, j, 0));
            for (auto x : tree[i])
                for (auto y : tree[i])
                    if (x != y) graph[_(x, j, 1)].push_back(_(y, j, 0));
        }
    dfs(0);
    while (q--) {
        int r, a, b, x;
        cin >> r >> a >> b >> x;
        int y = -1;
        if (dfni[x] <= dfni[r] && dfni[r] <= dfno[x]) {
            if (x != r) {
                for (auto i : tree[x])
                    if (dfni[i] <= dfni[r] && dfni[r] <= dfno[i]) y = i;
                graph[_(y, a, 1)].push_back(_(y, a, 0)), graph[_(y, b, 1)].push_back(_(y, b, 0));
            }
            if (x) graph[_(x, a, 0)].push_back(_(x, b, 1)), graph[_(x, b, 0)].push_back(_(x, a, 1));
        } else
            graph[_(x, a, 0)].push_back(_(x, a, 1)), graph[_(x, b, 0)].push_back(_(x, b, 1));
        for (auto i : tree[x])
            if (i != y) graph[_(i, a, 1)].push_back(_(i, b, 0)), graph[_(i, b, 1)].push_back(_(i, a, 0));
    }
    memset(scc, 0xff, sizeof(scc));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int t = 0; t < 2; t++)
                if (!~scc[_(i, j, t)]) tarjan(_(i, j, t));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scc[_(i, j, 0)] == scc[_(i, j, 1)]) return cout << -1 << endl, void();
    for (int j = 0; j < m; j++) {
        int d = 0;
        for (int i = 0; i < n; i++)
            if (scc[_(i, j, 0)] > scc[_(i, j, 1)] && (!~d || dep[i] > dep[d])) d = i;
        cout << d << ' ';
    }
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("hide.in", "r", stdin), freopen("hide.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
