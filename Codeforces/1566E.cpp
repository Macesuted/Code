/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

vector<set<int>> graph;

int restLeaf;
queue<int> cache;
int fa[maxn];

void check(int p) {
    if (p == 1 || p == -1 || graph[p].empty()) return;
    for (auto i : graph[p])
        if (!graph[i].empty()) return;
    cache.push(p);
    return;
}
void dfs(int p, int pre = -1) {
    if (pre != -1) graph[p].erase(pre);
    restLeaf += graph[p].empty();
    fa[p] = pre;
    for (auto i : graph[p]) dfs(i, p);
    check(p);
    return;
}

void work(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (register int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        graph[x].insert(y), graph[y].insert(x);
    }
    restLeaf = 0;
    dfs(1);
    int answer = restLeaf;
    while (!cache.empty()) {
        int p = cache.front();
        cache.pop();
        int siz = graph[p].size();
        if (siz == restLeaf) break;
        restLeaf -= siz;
        graph[fa[p]].erase(p);
        answer--;
        if (graph[fa[p]].empty()) answer++, restLeaf++;
        check(fa[p]), check(fa[fa[p]]);
    }
    while (!cache.empty()) cache.pop();
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}