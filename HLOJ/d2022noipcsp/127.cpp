/**
 * @file color.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-13
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

#define maxn 1005

vector<vector<int>> graph;
int col[maxn], cnt[maxn][3];
bool chk[maxn];

void dfs1(int p) {
    for (auto i : graph[p]) dfs1(i), cnt[p][col[i]]++;
    if (cnt[p][1] > cnt[p][2]) col[p] = 1;
    if (cnt[p][1] < cnt[p][2]) col[p] = 2;
    return;
}
void dfs2(int p) {
    if (graph[p].empty()) chk[p] = true;
    for (auto i : graph[p])
        if (col[i] == 0 || cnt[i][1] - cnt[i][2] == 1) dfs2(i);
    return;
}

void solve(void) {
    int n;
    cin >> n, graph.resize(n + 1);
    for (int i = 1, c; i <= n; i++) {
        cin >> c;
        if (c <= 0)
            col[i] = -c;
        else
            for (int j = 0, p; j < c; j++) cin >> p, graph[i].push_back(p);
    }
    dfs1(1);
    if (col[1] == 1) return cout << "Bob" << endl, void();
    cout << "Alice" << endl;
    if (col[1] == 0) dfs2(1);
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if ((col[1] == 2 && graph[i].empty() && col[i] == 0) || chk[i]) ans.push_back(i);
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("color.in", "r", stdin), freopen("color.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}