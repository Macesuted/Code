/**
 * @file 15479.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

using pll = pair<int64_t, int64_t>;

vector<int> graph[maxn];
pll a[maxn], fu[maxn], fd[maxn];
int dep[maxn];
vector<pll> ques[maxn];
int64_t ans[maxn];

int siz[maxn];
bool vis[maxn];

pll merge(const pll& x, const pll& y) { return {max(x.first, y.first - x.second), x.second + y.second}; }

void getSiz(int p, int pre = -1) {
    siz[p] = 1;
    for (auto q : graph[p])
        if (q != pre && !vis[q]) getSiz(q, p), siz[p] += siz[q];
    return;
}
int getRoot(int p, int tot, int pre = -1) {
    for (auto q : graph[p])
        if (q != pre && !vis[q] && siz[q] > tot - siz[q]) return getRoot(q, tot, p);
    return p;
}

void dfs0(int p, int pre = -1) {
    for (auto q : graph[p])
        if (q != pre) dep[q] = dep[p] + 1, dfs0(q, p);
    return;
}

void dfs1(int p, int pre) {
    fu[p] = merge(a[p], fu[pre]), fd[p] = merge(fd[pre], a[p]);
    for (auto q : graph[p])
        if (q != pre && !vis[q]) dfs1(q, p);
    return;
}

set<pll> S;
int64_t getAns(int64_t x) {
    auto p = S.lower_bound({x + 1, INT64_MIN});
    return p == S.begin() ? INT64_MIN : x + prev(p)->second;
}
void insert(pll v) {
    auto p = S.lower_bound({v.first + 1, INT64_MIN});
    if (p != S.begin() && prev(p)->second >= v.second) return;
    p = next(S.insert(v).first);
    while (p != S.end() && p->second <= v.second) p = S.erase(p);
    return;
}
void dfs2(int p, int pre = -1) {
    for (auto [x, id] : ques[p])
        if (x >= fu[p].first) ans[id] = max(ans[id], getAns(x + fu[p].second));

    for (auto q : graph[p])
        if (q != pre && !vis[q] && dep[q] < dep[p]) dfs2(q, p);

    return;
}
void dfs3(int p, int pre = -1) {
    insert(fd[p]);
    for (auto q : graph[p])
        if (q != pre && !vis[q] && dep[q] > dep[p]) dfs3(q, p);
    return;
}

void dfs(int p) {
    getSiz(p);
    p = getRoot(p, siz[p]);

    fu[p] = {0, 0}, fd[p] = a[p];
    for (auto q : graph[p])
        if (!vis[q]) dfs1(q, p);

    S.clear(), insert(fd[p]);
    for (auto q : graph[p])
        if (!vis[q] && dep[q] > dep[p]) dfs3(q, p);

    for (auto [x, id] : ques[p]) ans[id] = max(ans[id], getAns(x));

    for (auto q : graph[p])
        if (!vis[q] && dep[q] < dep[p]) dfs2(q, p);

    vis[p] = true;
    for (auto q : graph[p])
        if (!vis[q]) dfs(q);

    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) cin >> a[i].second;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second -= a[i].first;

    for (int i = 1, p; i <= q; i++) {
        int64_t x;
        cin >> p >> x, ques[p].emplace_back(x, i), ans[i] = x;
    }

    dfs0(1);

    dfs(2);

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
