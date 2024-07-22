/**
 * @file D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-21
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

#define maxn 100005

typedef pair<int64_t, int> pli;

int64_t a[maxn], siz[maxn];
vector<int> graph[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = a[p];
    for (auto i : graph[p])
        if (i != pre) dfs1(i, p), siz[p] += siz[i];
    return;
}
pli dfs2(int p, int pre = -1) {
    int64_t maxv = 0;
    for (auto i : graph[p]) maxv = max(maxv, siz[i]);
    pli ans = {maxv, p};
    for (auto i : graph[p])
        if (i != pre) {
            siz[p] -= siz[i], siz[i] += siz[p];
            ans = min(ans, dfs2(i, p));
            siz[i] -= siz[p], siz[p] += siz[i];
        }
    return ans;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1);
    cout << dfs2(1).second << endl;
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