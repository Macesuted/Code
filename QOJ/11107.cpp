/**
 * @file 11107.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-13
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

map<int, pii> graph[maxn];
multiset<int> near[maxn];
bool ban[maxn];

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, x, y, c, t; i <= m; i++)
        cin >> x >> y >> c >> t, graph[x][y] = graph[y][x] = {c, t}, near[x].insert(t), near[y].insert(t);

    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (near[i].empty() || *near[i].begin() == *near[i].rbegin()) ban[i] = true, que.push(i);

    vector<pii> ans;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (near[p].empty()) continue;
        ans.emplace_back(p, *near[p].begin());
        for (auto [q, w] : graph[p]) {
            auto [c, t] = w;
            near[p].erase(near[p].find(t)), near[q].erase(near[q].find(t));
            graph[q].erase(p);
            if (!ban[q] && (near[q].empty() || *near[q].begin() == *near[q].rbegin())) ban[q] = true, que.push(q);
        }
        graph[p].clear();
    }

    for (int p = 1; p <= n; p++)
        for (auto [q, w] : graph[p])
            if (w.first != w.second) return cout << -1 << endl, void();

    cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    for (auto [p, t] : ans) cout << p << ' ' << t << endl;

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