/**
 * @file 1801D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-09
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

#define maxn 805

typedef pair<int, int> pii;
typedef pair<int64_t, int> pIi;
typedef tuple<pIi, int, int> tpii;

int a[maxn];
vector<pii> graph[maxn];
pIi dist[maxn][maxn];
bool vis[maxn][maxn];
priority_queue<tpii, vector<tpii>, greater<tpii>> que;

void solve(void) {
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> a[i], graph[i].clear();
    for (int i = 1, x, y, c; i <= m; i++) cin >> x >> y >> c, graph[x].emplace_back(y, c);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) dist[i][j] = {INT64_MAX, 0}, vis[i][j] = false;
    que.emplace(dist[1][1] = {0, -p}, 1, 1);
    while (!que.empty()) {
        int x = get<1>(que.top()), y = get<2>(que.top());
        que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        int c = -dist[x][y].second;
        for (auto i : graph[x]) {
            int t = max(0, i.second - c) / a[y], u = (a[y] < a[i.first] ? i.first : y);
            if (c + a[y] * t < i.second) t++;
            pIi d = {dist[x][y].first + t, -(t * a[y] + c - i.second)};
            if (dist[i.first][u] > d) que.emplace(dist[i.first][u] = d, i.first, u);
        }
    }
    int64_t ans = INT64_MAX;
    for (int i = 1; i <= n; i++) ans = min(ans, dist[n][i].first);
    cout << (ans == INT64_MAX ? -1 : ans) << endl;
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