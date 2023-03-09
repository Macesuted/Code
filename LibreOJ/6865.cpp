/**
 * @file 6865.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int a[maxn], siz[maxn], dep[maxn], dfni[maxn], dfno[maxn];
vector<int> graph[maxn];

int dfnt = 0;
void dfs(int p, int pre = 0) {
    dep[p] = dep[pre] + 1, siz[p] = 1, dfni[p] = ++dfnt;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p), siz[p] += siz[i];
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2, x; i <= n; i++) cin >> x, graph[x].push_back(i);
    dep[0] = -1, dfs(1);
    for (int i = 1; i <= n; i++) a[i] = siz[i] - 1 - a[i] - dep[i];
    sort(a + 1, a + n + 1, greater<int>());
    int64_t sum = 0;
    for (int i = 1; i <= n; i += 2) sum += a[i];
    cout << sum << endl;
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