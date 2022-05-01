/**
 * @file 1627C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

vector<vector<pii>> graph;
int ans[maxn];

void dfs(int p, int col = 1, int pre = -1) {
    for (auto i : graph[p])
        if (i.first != pre)
            ans[i.second] = col, dfs(i.first, !col, p);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].emplace_back(y, i), graph[y].emplace_back(x, i);
    }
    for (int i = 1; i <= n; i++)
        if ((int)graph[i].size() > 2)
            return cout << -1 << endl, void();
    for (int i = 1; i <= n; i++)
        if ((int)graph[i].size() == 1) {
            dfs(i);
            break;
        }
    for (int i = 1; i < n; i++) cout << (ans[i] ? 2 : 3) << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
