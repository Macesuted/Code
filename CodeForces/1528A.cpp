/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int l[maxn], r[maxn];
long long f[maxn][2];

vector<vector<int> > graph;

void dfs(int p, int pre) {
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs(*i, p);
    f[p][0] = f[p][1] = 0;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            f[p][0] += max(abs(l[p] - l[*i]) + f[*i][0], abs(l[p] - r[*i]) + f[*i][1]);
            f[p][1] += max(abs(r[p] - l[*i]) + f[*i][0], abs(r[p] - r[*i]) + f[*i][1]);
        }
    return;
}

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> l[i] >> r[i];
    graph.resize(n + 1);
    for (register int i = 1, from, to; i < n; i++) {
        cin >> from >> to;
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs(1, -1);
    cout << max(f[1][0], f[1][1]) << endl;
    graph.clear();
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}