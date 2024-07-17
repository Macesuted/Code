/**
 * @file 535265I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

typedef pair<int, int> pii;

int n, m;
string a[maxn];
int dis[maxn * maxn * 5], indeg[maxn * maxn * 5];

int _(int x, int y, int t) { return t * n * m + (x - 1) * m + y; }

vector<vector<pii>> graph;

vector<int> rec;
set<int> S;
bool dfs(int p) {
    if (!p) return false;
    if (dis[p] == -2) return true;
    if (dis[p] >= 0) return false;
    dis[p] = -2, rec.push_back(p);
    bool ret = dfs(graph[p].front().first);
    if (graph[p].front().second == 1) S.insert(p % (n * m));
    dis[p] = S.size();
    return ret;
}

int main() {
    cin >> n >> m;
    graph.resize(_(n, m, 3) + 1);
    for (int i = 1; i <= _(n, m, 3); i++) dis[i] = -1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i], a[i] = ' ' + a[i];
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '-') {
                graph[_(i, j, 0)].emplace_back(i < n ? _(i + 1, j, 1) : 0, 1);
                graph[_(i, j, 1)].emplace_back(i > 1 ? _(i - 1, j, 0) : 0, 1);
                graph[_(i, j, 2)].emplace_back(j > 1 ? _(i, j - 1, 2) : 0, 0);
                graph[_(i, j, 3)].emplace_back(j < m ? _(i, j + 1, 3) : 0, 0);
            } else if (a[i][j] == '|') {
                graph[_(i, j, 0)].emplace_back(i > 1 ? _(i - 1, j, 0) : 0, 0);
                graph[_(i, j, 1)].emplace_back(i < n ? _(i + 1, j, 1) : 0, 0);
                graph[_(i, j, 2)].emplace_back(j < m ? _(i, j + 1, 3) : 0, 1);
                graph[_(i, j, 3)].emplace_back(j > 1 ? _(i, j - 1, 2) : 0, 1);
            } else if (a[i][j] == '/') {
                graph[_(i, j, 0)].emplace_back(j < m ? _(i, j + 1, 3) : 0, 1);
                graph[_(i, j, 1)].emplace_back(j > 1 ? _(i, j - 1, 2) : 0, 1);
                graph[_(i, j, 2)].emplace_back(i < n ? _(i + 1, j, 1) : 0, 1);
                graph[_(i, j, 3)].emplace_back(i > 1 ? _(i - 1, j, 0) : 0, 1);
            } else {
                graph[_(i, j, 0)].emplace_back(j > 1 ? _(i, j - 1, 2) : 0, 1);
                graph[_(i, j, 1)].emplace_back(j < m ? _(i, j + 1, 3) : 0, 1);
                graph[_(i, j, 2)].emplace_back(i > 1 ? _(i - 1, j, 0) : 0, 1);
                graph[_(i, j, 3)].emplace_back(i < n ? _(i + 1, j, 1) : 0, 1);
            }
    }

    for (int i = 1; i <= _(n, m, 3); i++)
        for (auto j : graph[i]) indeg[j.first]++;
    for (int i = 1; i <= _(n, m, 3); i++)
        if (!indeg[i]) rec.clear(), S.clear(), dfs(i);

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        string op;
        cin >> x >> y >> op;

        int p = 0;
        if (op == "above") {
            if (x == 1) {
                cout << 0 << endl;
                continue;
            }
            p = _(x - 1, y, 0);
        } else if (op == "below") {
            if (x == n) {
                cout << 0 << endl;
                continue;
            }
            p = _(x + 1, y, 1);
        } else if (op == "left") {
            if (y == 1) {
                cout << 0 << endl;
                continue;
            }
            p = _(x, y - 1, 2);
        } else {
            if (y == m) {
                cout << 0 << endl;
                continue;
            }
            p = _(x, y + 1, 3);
        }

        if (dis[p] != -1) {
            cout << dis[p] << endl;
            continue;
        }

        rec.clear(), S.clear();
        bool ret = dfs(p);
        if (ret)
            for (auto i : rec) dis[i] = S.size();

        cout << dis[p] << endl;
    }
    return 0;
}