/**
 * @file 5428.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;

const int way[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};

string a[maxn];
vector<int> graph[maxn * maxn];
bool vis[maxn * maxn];
int dist[maxn * maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--, c1--, r2--, c2--;
    auto _ = [&](int x, int y) { return x * m + y; };
    for (int i = 0; i < n; i++)
        for (int j = 0, l = j; j < m; j++)
            if (a[i][j] == '#')
                l = j + 1;
            else
                graph[_(i, j)].push_back(_(i, l));
    for (int i = 0; i < n; i++)
        for (int j = m - 1, l = j; ~j; j--)
            if (a[i][j] == '#')
                l = j - 1;
            else
                graph[_(i, j)].push_back(_(i, l));
    for (int j = 0; j < m; j++)
        for (int i = 0, l = i; i < n; i++)
            if (a[i][j] == '#')
                l = i + 1;
            else
                graph[_(i, j)].push_back(_(l, j));
    for (int j = 0; j < m; j++)
        for (int i = n - 1, l = i; ~i; i--)
            if (a[i][j] == '#')
                l = i - 1;
            else
                graph[_(i, j)].push_back(_(l, j));
    static priority_queue<pii, vector<pii>, greater<pii>> que;
    memset(dist, 0x3f, sizeof(dist));
    que.emplace(dist[_(r1, c1)] = 0, _(r1, c1));
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        int r = p / m, c = p % m;
        for (auto i : graph[p])
            if (dist[i] > dist[p] + 1) que.emplace(dist[i] = dist[p] + 1, i);
        for (int t = 0; t < 4; t++) {
            int x = r + way[0][t], y = c + way[1][t];
            if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] == '#') continue;
            if (dist[_(x, y)] > dist[p] + 2) que.emplace(dist[_(x, y)] = dist[p] + 2, _(x, y));
        }
    }
    cout << (dist[_(r2, c2)] == 0x3f3f3f3f ? -1 : dist[_(r2, c2)]) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
