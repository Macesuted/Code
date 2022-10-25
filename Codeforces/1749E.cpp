/**
 * @file 1749E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-20
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

#define maxn 200005

typedef pair<int, int> pii;

string s[maxn];
vector<vector<pii>> graph;
vector<int> dist, pre;
vector<bool> vis;
priority_queue<pii, vector<pii>, greater<pii>> que;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = " " + s[i];
    int S = n * m + 1, T = S + 1;
    graph.clear(), graph.resize(T + 1);
    auto _ = [&](int x, int y) { return (x - 1) * m + y; };
    for (int i = 1; i <= n; i++) {
        graph[S].emplace_back(_(i, 1), s[i][1] == '.');
        for (int j = 1; j <= m; j++) {
            if (i > 1 && j > 1) graph[_(i, j)].emplace_back(_(i - 1, j - 1), s[i - 1][j - 1] == '.');
            if (i > 1 && j < m) graph[_(i, j)].emplace_back(_(i - 1, j + 1), s[i - 1][j + 1] == '.');
            if (i < n && j > 1) graph[_(i, j)].emplace_back(_(i + 1, j - 1), s[i + 1][j - 1] == '.');
            if (i < n && j < m) graph[_(i, j)].emplace_back(_(i + 1, j + 1), s[i + 1][j + 1] == '.');
        }
        graph[_(i, m)].emplace_back(T, 0);
    }
    dist.clear(), dist.resize(T + 1, INT_MAX), vis.clear(), vis.resize(T + 1, false), pre.clear(), pre.resize(T + 1);
    que.emplace(dist[S] = 0, S);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        if (p != S && p != T) {
            int x = (p - 1) / m + 1, y = (p - 1) % m + 1;
            if ((x > 1 && s[x - 1][y] == '#') || (x < n && s[x + 1][y] == '#') || (y > 1 && s[x][y - 1] == '#') ||
                (y < m && s[x][y + 1] == '#'))
                continue;
        }
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second)
                que.emplace(dist[i.first] = dist[p] + i.second, i.first), pre[i.first] = p;
    }
    if (dist[T] == INT_MAX) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    int p = pre[T];
    while (p != S) s[(p - 1) / m + 1][(p - 1) % m + 1] = '#', p = pre[p];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << s[i][j];
        cout << endl;
    }
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