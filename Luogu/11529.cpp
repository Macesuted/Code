/**
 * @file 11529.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

int bl[maxn], deg[maxn];
bool ban[maxn], col[maxn], vis[maxn];
vector<int> graph[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> bl[i], col[bl[i]] = true;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) deg[i] = graph[i].size();
    for (int i = 1; i <= k; i++)
        for (auto p : graph[bl[i]])
            if (!col[p]) ban[p] = true;

    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1) que.push(i);

    int ans = 0;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        vis[p] = true;
        if (ban[p]) {
            int q = -1;
            for (auto i : graph[p])
                if (!vis[i]) q = i;
            ans++;
            if (!col[q]) {
                ban[q] = false;
                for (auto r : graph[q]) ban[r] = false;
            }
        }
        for (auto i : graph[p])
            if (!vis[i] && --deg[i] == 1) que.push(i);
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i] && ban[i]) ans++;

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