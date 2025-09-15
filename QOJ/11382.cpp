/**
 * @file 11382.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-13
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

#define maxn 100005

using pii = pair<int, int>;
using tlii = tuple<int64_t, int, int>;

int a[maxn];
int64_t ans[maxn];
vector<pii> graph[maxn];

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;

    priority_queue<tlii, vector<tlii>, greater<tlii>> que;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], ans[i] = -1;
        if (!a[i]) a[i] = 1, que.emplace(0, i, 1);
    }

    for (int i = 1, t, sc; i <= k; i++) {
        cin >> t >> sc;
        for (int j = 1, x; j <= sc; j++) cin >> x, que.emplace(t, x, INT_MAX);
    }

    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w);

    while (!que.empty()) {
        auto [t, p, d] = que.top();
        que.pop();
        if (!a[p] || (a[p] = max(0, a[p] - d)) > 0) continue;
        ans[p] = t;
        for (auto [q, w] : graph[p]) que.emplace(t + w, q, 1);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}