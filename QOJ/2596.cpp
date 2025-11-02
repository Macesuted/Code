/**
 * @file 2596.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

using pii = pair<int, int>;

vector<int> graph[maxn];
int f[maxn][3];

void dfs(int p, int pre = -1) {
    vector<int> rec[2];
    int sum = 0;

    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs(q, p);
        sum += f[q][2];
        if (f[q][0] != INT_MAX) rec[0].push_back(f[q][0] - f[q][2]);
        if (f[q][1] != INT_MAX) rec[1].push_back(f[q][1] - f[q][2]);
    }
    sort(rec[0].begin(), rec[0].end()), sort(rec[1].begin(), rec[1].end());

    f[p][0] = f[p][1] = f[p][2] = INT_MAX;
    if (rec[1].size() >= 0) {
        f[p][0] = sum;
        for (size_t i = 0; i < rec[1].size() && rec[1][i] < 0; i++) f[p][0] += rec[1][i];
    }
    if (rec[0].size() >= 1) {
        f[p][1] = sum + rec[0][0];
        for (size_t i = 1; i < rec[0].size() && rec[0][i] < 0; i++) f[p][1] += rec[0][i];
    }

    if (rec[0].size() >= 2) {
        int val = 1 + sum + rec[0][0] + rec[0][1];
        for (size_t i = 2; i < rec[0].size() && rec[0][i] < 0; i++) val += rec[0][i];
        f[p][2] = min(f[p][2], val);
    }
    if (rec[1].size() >= 0) {
        int val = 1 + sum;
        for (size_t i = 0; i < rec[1].size() && rec[1][i] < 0; i++) val += rec[1][i];
        f[p][2] = min(f[p][2], val);
    }

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    if (n <= 2) return cout << n - 1 << endl, void();

    int root = 1;
    while (graph[root].size() == 1) root++;

    dfs(root);

    cout << f[root][2] - 1 << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
