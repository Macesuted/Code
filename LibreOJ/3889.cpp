/**
 * @file 3889.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-29
 *
 * @copyright Copyright (c) 2022
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 2505

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;

vector<int> graph[maxn];
queue<int> que;
int dist[maxn][maxn], f[maxn][3];
int64_t v[maxn];
int n, m, k;

void bfs(int S) {
    for (int i = 1; i <= n; i++) dist[S][i] = INT_MAX;
    dist[S][S] = 0, que.push(S);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (dist[S][p] == k) continue;
        for (auto i : graph[p])
            if (dist[S][i] > dist[S][p] + 1) dist[S][i] = dist[S][p] + 1, que.push(i);
    }
    return;
}

void solve(void) {
    cin >> n >> m >> k, k++;
    for (int i = 2; i <= n; i++) cin >> v[i];
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) bfs(i);
    v[0] = -1e18;
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++)
            if (i != j && dist[i][j] <= k && dist[1][j] <= k) {
                if (v[j] > v[f[i][0]])
                    f[i][2] = f[i][1], f[i][1] = f[i][0], f[i][0] = j;
                else if (v[j] > v[f[i][1]])
                    f[i][2] = f[i][1], f[i][1] = j;
                else if (v[j] > v[f[i][2]])
                    f[i][2] = j;
            }
    int64_t ans = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++)
            if (i != j && dist[i][j] <= k) {
                int p1 = 0, p2 = 0;
                if (f[i][p1] == j) p1++;
                if (f[j][p2] == i) p2++;
                if (!f[i][p1] || !f[j][p2]) continue;
                if (f[i][p1] != f[j][p2]) {
                    ans = max(ans, v[f[i][p1]] + v[i] + v[j] + v[f[j][p2]]);
                    continue;
                }
                int p = p1 + 1;
                if (f[i][p] == j) p++;
                if (f[i][p]) ans = max(ans, v[f[i][p]] + v[i] + v[j] + v[f[j][p2]]);
                p = p2 + 1;
                if (f[j][p] == i) p++;
                if (f[i][p1]) ans = max(ans, v[f[i][p1]] + v[i] + v[j] + v[f[j][p]]);
            }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("holiday.in", "r", stdin), freopen("holiday.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}