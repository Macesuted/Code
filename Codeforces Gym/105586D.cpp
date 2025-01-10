/**
 * @file 105586D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

vector<int> graph[maxn];
int a[maxn], indeg[maxn];
int64_t f[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], f[i] = INT_MAX;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[y].push_back(x), indeg[x]++;

    int64_t ans = INT64_MAX;
    queue<int> que;
    que.push(n), f[n] = a[n] / 2 + 1;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (graph[p].empty()) ans = min(ans, f[p]);
        for (auto q : graph[p]) {
            if (2 * a[q] <= f[p])
                f[q] = min(f[q], f[p] - a[q]);
            else if (a[q] - 2 < f[p])
                f[q] = min(f[q], (int64_t)a[q]);
            else
                f[q] = min(f[q], (f[p] + a[q] + 1) / 2);
            if (!--indeg[q]) que.push(q);
        }
    }
    cout << ans << endl;
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