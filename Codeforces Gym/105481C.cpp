/**
 * @file 105481C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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
vector<int64_t> rec, vis;
int64_t a[maxn];

void dfs(int p) {
    if (graph[p].empty()) return;
    a[p] = 0;
    for (auto i : graph[p]) dfs(i), a[p] += a[i];
    return;
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1, f; i <= n; i++) cin >> f >> a[i], graph[f].push_back(i);

    for (int i = 1; i <= n; i++)
        if (!graph[i].empty()) rec.push_back(a[i]);
    sort(rec.begin(), rec.end());

    dfs(0);
    if (a[0] > 2200) return cout << "NO" << endl, void();

    for (int i = 1; i <= n; i++)
        if (!graph[i].empty()) vis.push_back(a[i]);
    sort(vis.begin(), vis.end());

    for (int i = 0; i < (int)rec.size(); i++)
        if (vis[i] > rec[i]) return cout << "NO" << endl, void();

    cout << "YES" << endl;

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