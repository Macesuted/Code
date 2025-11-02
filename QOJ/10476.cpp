/**
 * @file 10476.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

using pli = pair<int64_t, int>;

vector<pli> graph[maxn];
int64_t a[maxn], dist[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], dist[i] = INT64_MAX;
    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, graph[x].emplace_back(w, y), graph[y].emplace_back(w, x);

    priority_queue<pli, vector<pli>, greater<pli>> que;
    que.emplace(dist[1] = 0, 1);
    while (!que.empty()) {
        auto [d, p] = que.top();
        que.pop();
        if (d != dist[p]) continue;
        for (auto [w, q] : graph[p])
            if (dist[q] > dist[p] + w) que.emplace(dist[q] = dist[p] + w, q);
    }

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += dist[i] * a[i];
    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
