/**
 * @file 2053E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-28
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

#define maxn 200005

vector<vector<int>> graph;
vector<int> f;
vector<bool> leaf, ban;
int cntD2;

void dfs1(int p, int pre = -1) {
    f[p] = !ban[p];
    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs1(q, p);
        f[p] += f[q];
    }
    return;
}
int64_t dfs2(int p, int pre = -1) {
    int64_t ans = 0;
    if (leaf[p]) ans = cntD2;

    if (ban[p]) {
        int cnt = 0;
        for (auto q : graph[p]) cnt += !leaf[q];
        for (auto q : graph[p])
            if (!leaf[q]) ans += (int64_t)(cnt - 1) * f[q];
    }

    for (auto q : graph[p])
        if (q != pre) {
            f[p] -= f[q], f[q] += f[p];
            ans += dfs2(q, p);
            f[q] -= f[p], f[p] += f[q];
        }
    return ans;
}

void solve(void) {
    int n;
    cin >> n;

    graph = vector<vector<int>>(n + 1);
    leaf = ban = vector<bool>(n + 1);
    f = vector<int>(n + 1);

    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    if (n == 2) return cout << 0 << endl, void();

    for (int i = 1; i <= n; i++) leaf[i] = (graph[i].size() == 1);

    for (int i = 1; i <= n; i++) {
        if (leaf[i] == 1) {
            ban[i] = true;
            continue;
        }
        for (auto j : graph[i])
            if (graph[j].size() == 1) ban[i] = true;
    }
    cntD2 = 0;
    for (int i = 1; i <= n; i++) cntD2 += !leaf[i];

    dfs1(1);

    cout << dfs2(1) << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}