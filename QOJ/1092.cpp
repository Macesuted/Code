/**
 * @file 1092.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

vector<int> graph[maxn];
int col[maxn], cnt[3];

void dfs(int p, int c) {
    cnt[col[p] = c]++;
    for (auto q : graph[p])
        if (!col[q]) dfs(q, 3 - c);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!col[i]) {
            cnt[1] = cnt[2] = 0;
            dfs(i, 1);
            ans += min(cnt[1], cnt[2]);
        }

    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (col[i] == col[j]) return cout << -1 << endl, void();

    cout << max(1, ans) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
