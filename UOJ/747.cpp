/**
 * @file trip.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-06
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

#define maxn 100005
#define maxk 25

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;

vector<pii> graph[maxn];
int64_t dist[maxk][maxn];
priority_queue<pli, vector<pli>, greater<pli>> que;
bool vis[maxn];
vector<pli> vec;

void Dijkstra(int S, int64_t d[]) {
    memset(vis, 0, sizeof(vis)), que.emplace(d[S] = 0, S);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (d[i.first] > d[p] + i.second) que.emplace(d[i.first] = d[p] + i.second, i.first);
    }
    return;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m;
    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w * 2), graph[y].emplace_back(x, w * 2);
    memset(dist, 0x3f, sizeof(dist)), Dijkstra(1, dist[0]);
    cin >> k;
    for (int i = 1, x; i <= k; i++) cin >> x, Dijkstra(x, dist[i]);
    int64_t ans = INT64_MAX;
    for (int i = 1; i <= n; i++) {
        int64_t maxv = 0;
        for (int j = 0; j <= k; j++) maxv = max(maxv, dist[j][i]);
        ans = min(ans, maxv);
    }
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (i < j.first) {
                int x = i, y = j.first, w = j.second;
                int64_t vy = 0;
                vec.clear();
                for (int p = 0; p <= k; p++) vec.emplace_back(dist[p][x], p);
                sort(vec.begin(), vec.end());
                while (vec.size() > 1) {
                    int p = vec.back().second;
                    vec.pop_back(), vy = max(vy, dist[p][y]);
                    int64_t vx = vec.back().first;
                    if (abs(vx - vy) >= w) continue;
                    ans = min(ans, max(vx, vy) + (w - abs(vx - vy)) / 2);
                }
            }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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