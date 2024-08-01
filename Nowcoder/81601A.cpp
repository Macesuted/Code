/**
 * @file 81601A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

typedef pair<int, int> pii;

vector<vector<pii>> graph;
int cnt[maxn][2];
double f[maxn];

void dfs1(int p, int pre = -1) {
    for (auto [i, t] : graph[p])
        if (i != pre) cnt[i][0] = cnt[p][0], cnt[i][1] = cnt[p][1], cnt[i][t]++, dfs1(i, p);
    return;
}
void dfs2(int p, int pre = -1) {
    if (p != 1) f[p] = min(f[pre], (double)cnt[p][1] / (cnt[p][0] + cnt[p][1]));
    for (auto [i, t] : graph[p])
        if (i != pre) dfs2(i, p);
    return;
}
void dfs3(int p, int pre = -1, int op = 0) {
    bool vis = false;
    for (auto [i, t] : graph[p])
        if (i != pre) dfs3(i, p, !op), vis = true;
    if (!vis) return;
    if (op == 0) {
        f[p] = 0;
        for (auto [i, t] : graph[p])
            if (i != pre) f[p] = max(f[p], f[i]);
    } else {
        f[p] = 1;
        for (auto [i, t] : graph[p])
            if (i != pre) f[p] = min(f[p], f[i]);
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y, t; i < n; i++) cin >> x >> y >> t, graph[x].emplace_back(y, t), graph[y].emplace_back(x, t);
    cnt[1][0] = cnt[1][1] = 0, dfs1(1);
    f[1] = 1, dfs2(1);
    dfs3(1);
    cout << f[1] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    cout << setiosflags(ios::fixed) << setprecision(12);
    while (_--) solve();

    return 0;
}