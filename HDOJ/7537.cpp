/**
 * @file 7537.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 4005

bool mem1;

typedef pair<int, int> pii;

const int64_t INF = 1e18;

int b[maxn], siz[maxn];
int64_t K;
vector<int64_t> f[2][maxn];
vector<vector<pii>> graph;

int64_t& F(int x, int y, int t) { return f[t][x][y + (f[t][x].size() >> 1)]; }

void dfs(int p, int pre = -1) {
    // cerr << "! " << p << endl;
    f[0][p] = f[1][p] = vector<int64_t>((siz[p] = 1) * 2 + 1, INF);
    F(p, 0, 0) = F(p, 0, 1) = F(p, 1, 0) = F(p, 1, 1) = 0;
    if (b[p]) F(p, -1, 1) = 0;
    for (auto [q, d] : graph[p]) {
        if (q == pre) continue;
        dfs(q, p);
        f[0][0] = f[0][p], f[1][0] = f[1][p];
        f[0][p] = f[1][p] = vector<int64_t>((siz[p] + siz[q]) * 2 + 1, INF);
        for (int i = -siz[p]; i <= siz[p]; i++)
            for (int j = -siz[q]; j <= siz[q]; j++) {
                F(p, i + j, 0) = min(F(p, i + j, 0), F(0, i, 0) + F(q, j, 0) + abs(j) * K);
                F(p, i + j, 1) = min(F(p, i + j, 1), F(0, i, 1) + min(F(q, j, 0), F(q, j, 1) + d) + abs(j) * K);
            }
        siz[p] += siz[q];
    }
    F(p, 0, 0) = INF;
    return;
}

void solve(void) {
    int n;
    cin >> n >> K, K *= 2;
    for (int i = 1; i <= n; i++) cin >> b[i];
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y, w; i < n; i++) cin >> x >> y >> w, w <<= 1, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);
    dfs(1);
    cout << F(1, 0, 1) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}