/**
 * @file 7524.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 200005

vector<vector<int>> graph;
int siz[maxn], f[maxn], vl[maxn], vr[maxn], a[maxn], b[maxn];

void dfs1(int p) {
    siz[p] = 1, f[p] = p;
    for (auto i : graph[p]) dfs1(i), siz[p] += siz[i], f[p] = min(f[p], f[i]);
    sort(graph[p].begin(), graph[p].end(), [&](int x, int y) { return f[x] < f[y]; });
    return;
}
void dfs2(int p) {
    a[p] = vl[p] + siz[p] - 1, b[p] = vr[p];
    vr[p]--;
    for (auto i : graph[p]) {
        vl[i] = vl[p], vr[i] = vr[p];
        vl[p] += siz[i], vr[p] -= siz[i];
        dfs2(i);
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 2, x; i <= n; i++) cin >> x, graph[x].push_back(i);
    dfs1(1);
    vl[1] = 1, vr[1] = n, dfs2(1);
    for (int i = 1; i <= n; i++) cout << a[i] << ' ' << b[i] << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}