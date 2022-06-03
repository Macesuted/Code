/**
 * @file 2114.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-03
 *
 * @copyright Copyright (c) 2022
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
int indeg[maxn];
vector<int> ans;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) graph[i].clear(), indeg[i] = 0;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[y].push_back(x), indeg[x]++;
    static priority_queue<int, vector<int>, less<int>> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    ans.clear();
    while (!que.empty()) {
        int p = que.top();
        que.pop(), ans.push_back(p);
        for (auto i : graph[p])
            if (!--indeg[i]) que.push(i);
    }
    if ((int)ans.size() != n) return cout << "Impossible!" << endl, void();
    reverse(ans.begin(), ans.end());
    for (auto i : ans) cout << i << ' ';
    cout << endl;
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