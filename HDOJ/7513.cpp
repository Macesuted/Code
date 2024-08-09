/**
 * @file 7513.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

typedef pair<int, int> pii;

int64_t f[maxn];
vector<vector<pii>> graph;
int root;

void dfs(int p) {
    if (graph[p].empty()) return;
    vector<int64_t> cache;
    for (auto [i, x] : graph[p])
        if (i == root)
            return f[p] = 1e9 + 1, void();
        else
            dfs(i), cache.push_back(x * f[i]);
    sort(cache.begin(), cache.end()), reverse(cache.begin(), cache.end());
    f[p] = 0;
    for (int i = (p == root); i < (int)cache.size(); i++) f[p] += cache[i];
    f[p] = min(f[p], int64_t(1e9 + 1));
    return;
}

void solve(void) {
    int n;
    cin >> n >> root;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if (p == 0) {
            cin >> f[i];
            continue;
        }
        int t;
        cin >> t;
        while (t--) {
            int x, a;
            cin >> x >> a;
            graph[i].emplace_back(a, x);
        }
    }
    dfs(root);
    if (f[root] > 1e9) return cout << "Impossible" << endl, void();
    cout << f[root] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}