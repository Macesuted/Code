/**
 * @file C23013.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-12
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

#define maxn 10005
#define maxk 9

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

vector<pii> graph[maxn], a[maxn];
int dist[1 << maxk][maxn], ans[2][1 << maxk];
bool vis[maxn];
priority_queue<pii, vector<pii>, greater<pii>> que;

void solve(int n, int k, int st, int id) {
    memset(dist, 0x3f, sizeof(dist)), dist[0][st] = 0;
    for (int S = 0; S < (1 << k); S++) {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
            if (dist[S][i] != 0x3f3f3f3f) que.emplace(dist[S][i], i);
        while (!que.empty()) {
            int p = que.top().second;
            que.pop();
            if (vis[p]) continue;
            vis[p] = true;
            for (auto i : graph[p])
                if (dist[S][i.first] > dist[S][p] + i.second) que.emplace(dist[S][i.first] = dist[S][p] + i.second, i.first);
        }
        ans[id][S] = 0x3f3f3f3f;
        for (int i = 1; i <= n; i++) {
            ans[id][S] = min(ans[id][S], dist[S][i]);
            int T = S, p = 0;
            while (p != (int)a[i].size() && a[i][p].first < dist[S][i]) p++;
            while (p != (int)a[i].size()) T |= 1 << a[i][p].second, dist[T][i] = min(dist[T][i], a[i][p].first), p++;
        }
    }
    return;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);
    int q, tmax;
    cin >> q >> tmax;
    for (int i = 1, x, t, p; i <= q; i++) cin >> x >> p >> t, a[p].emplace_back(t, x - 1);
    for (int i = 1; i <= n; i++) sort(a[i].begin(), a[i].end());
    int x, y;
    cin >> x >> y;
    solve(n, k, x, 0), solve(n, k, y, 1);
    int answer = 0x3f3f3f3f;
    for (int S = 0; S < (1 << k); S++) answer = min(answer, max(ans[0][S], ans[1][~S & ((1 << k) - 1)]));
    cout << (answer > tmax ? -1 : answer) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("ghost.in", "r", stdin), freopen("ghost.out", "w", stdout);
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