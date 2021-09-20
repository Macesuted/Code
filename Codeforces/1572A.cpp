/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005
vector<vector<int>> graph;
int indeg[maxn];

void work(void) {
    int n;
    cin >> n;
    graph.resize(n + 1);
    memset(indeg, 0, sizeof(indeg));
    for (register int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        while (t--) {
            int p;
            cin >> p;
            graph[p].push_back(i), indeg[i]++;
        }
    }
    priority_queue<int, vector<int>, greater<int>> que;
    for (register int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    int cnt = 0, turns = 0;
    while (!que.empty()) {
        queue<int> cache;
        turns++;
        while (!que.empty()) {
            int p = que.top();
            que.pop();
            cnt++;
            for (auto i : graph[p])
                if (!--indeg[i]) i < p ? cache.push(i) : que.push(i);
        }
        while (!cache.empty()) que.push(cache.front()), cache.pop();
    }
    if (cnt != n)
        cout << -1 << endl;
    else
        cout << turns << endl;
    graph.clear();
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}