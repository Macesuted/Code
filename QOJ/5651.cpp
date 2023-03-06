/**
 * @file 5651.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
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

#define maxn 100005

vector<int> graph[maxn];
int f[maxn][2];

int dfs(int p, int dep = 0, int pre = 0) {
    int ans = (graph[p].size() == 1 ? p : 0);
    f[p][0] = p;
    vector<int> rec;
    for (auto i : graph[p])
        if (i != pre)
            ans = max(ans, dfs(i, dep + 1, p)), f[p][0] = max(f[p][0], f[i][1]), f[p][1] = max(f[p][1], f[i][0]),
            rec.push_back(f[i][1]);
    sort(rec.begin(), rec.end(), greater<int>());
    while (rec.size() < 3) rec.push_back(0);
    return max(ans, (dep & 1) ? 0 : rec[1 + !pre]);
}

void solve(void) {
    int n;
    cin >> n;
    if (!(n & 1)) return cout << n << endl, void();
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    cout << max(dfs(n), f[n][1]) << endl;
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