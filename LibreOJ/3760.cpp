/**
 * @file 3760.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 2005

typedef pair<int, int> pii;

int a[maxn], indeg[maxn];
vector<vector<int>> graph;
priority_queue<pii, vector<pii>, less<pii>> que;

void solve(void) {
    int n, m;
    cin >> n >> m, graph.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[y].push_back(x), indeg[x]++;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.emplace(a[i], i);
    vector<int> ans;
    while (!que.empty()) {
        int p = que.top().second;
        que.pop(), ans.push_back(p);
        for (auto i : graph[p])
            if (!--indeg[i]) que.emplace(a[i], i);
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans) cout << i << ' ';
    cout << endl;
    for (int s = 1; s <= n; s++) {
        for (int i = 1; i <= n; i++) indeg[i] = 0;
        for (int i = 1; i <= n; i++)
            for (auto j : graph[i]) indeg[j]++;
        while (!que.empty()) que.pop();
        for (int i = 1; i <= n; i++)
            if (!indeg[i]) que.emplace(a[i], i);
        int ans = n;
        while (!que.empty()) {
            int p = que.top().second;
            que.pop();
            if (p == s) continue;
            if (a[p] < ans) break;
            ans--;
            for (auto i : graph[p])
                if (!--indeg[i]) que.emplace(a[i], i);
        }
        cout << ans << ' ';
    }
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