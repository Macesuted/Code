/**
 * @file 10434.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

using pii = pair<int, int>;

int fa[maxn], indeg[maxn], ind[maxn];
vector<int> graph[maxn], nodes[maxn];
vector<pii> ans[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), fa[getfa(x)] = getfa(y), indeg[y]++;
    for (int i = 1; i <= n; i++) nodes[getfa(i)].push_back(i);

    for (int i = 1; i <= n; i++) {
        if (nodes[i].size() <= 1) continue;
        for (auto x : nodes[i]) ind[x] = indeg[x];

        auto calc = [&](int root) -> void {
            vector<int> rec;
            queue<int> que;
            que.push(root);
            for (auto x : nodes[i])
                if (!indeg[x] && x != root) que.push(x);
            while (!que.empty()) {
                int p = que.front();
                que.pop();
                rec.push_back(p);
                for (auto q : graph[p])
                    if (!--indeg[q] && q != root) que.push(q);
            }
            for (auto x : nodes[i]) indeg[x] = ind[x];
            if (rec.size() != nodes[i].size()) return;
            for (size_t x = 0; x + 1 < rec.size(); x++) ans[i].emplace_back(rec[x], rec[x + 1]);
            if (indeg[root]) ans[i].emplace_back(rec.back(), root);
            return;
        };

        ans[i].clear();
        for (int root : nodes[i])
            if (!indeg[root] && ans[i].empty()) calc(root);
        for (int root : nodes[i])
            if (indeg[root] && ans[i].empty()) calc(root);
        if (ans[i].empty()) return cout << -1 << endl, void();
    }

    int tot = 0;
    for (int i = 1; i <= n; i++) tot += ans[i].size();

    cout << tot << endl;
    for (int i = 1; i <= n; i++)
        for (auto [x, y] : ans[i]) cout << x << ' ' << y << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
