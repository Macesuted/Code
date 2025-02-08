/**
 * @file 100200B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
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

#define maxn 10005

typedef pair<int, int> pii;

vector<pii> graph[maxn];
int dfn[maxn], low[maxn];

int dfnt = 0;
vector<int> ans;
void tarjan(int p, int pre = -1) {
    dfn[p] = low[p] = ++dfnt;
    for (auto [q, id] : graph[p])
        if (!dfn[q]) {
            tarjan(q, p);
            low[p] = min(low[p], low[q]);
            if (low[q] > dfn[p]) ans.push_back(id);
        } else if (q == pre)
            pre = -1;
        else
            low[p] = min(low[p], dfn[q]);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].emplace_back(y, i), graph[y].emplace_back(x, i);

    tarjan(1);

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("bridges.in", "r", stdin), freopen("bridges.out", "w", stdout);
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