/**
 * @file 2090.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-09
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

#define maxn 20005
#define maxq 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int n, m;
vector<vector<pii>> graph;
priority_queue<pii, vector<pii>, greater<pii>> que;
int dist[maxn], ans[maxq];
bool vis[maxn];

int _(int x, int y) { return (x - 1) * m + y; }
pii $(int x) { return {(x - 1) / m + 1, (x - 1) % m + 1}; }

void Dijkstra(int S, int xl, int xr, int yl, int yr) {
    for (int x = xl; x <= xr; x++)
        for (int y = yl; y <= yr; y++) dist[_(x, y)] = 1e9, vis[_(x, y)] = false;
    que.emplace(dist[S] = 0, S);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (xl <= $(i.first).first && $(i.first).first <= xr && yl <= $(i.first).second && $(i.first).second <= yr &&
                dist[i.first] > dist[p] + i.second)
                que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }
    return;
}

void solve(int xl, int xr, int yl, int yr, vector<tiii> ques) {
    if (ques.empty()) return;
    if (xl == xr && yl == yr) {
        for (auto i : ques) ans[get<2>(i)] = 0;
        return;
    }
    if (xr - xl > yr - yl) {
        int xm = (xl + xr) >> 1;
        for (int y = yl; y <= yr; y++) {
            Dijkstra(_(xm, y), xl, xr, yl, yr);
            for (auto i : ques) ans[get<2>(i)] = min(ans[get<2>(i)], dist[get<0>(i)] + dist[get<1>(i)]);
        }
        vector<tiii> sque[2];
        for (auto i : ques)
            if (($(get<0>(i)).first <= xm) == ($(get<1>(i)).first <= xm)) sque[$(get<0>(i)).first > xm].push_back(i);
        solve(xl, xm, yl, yr, sque[0]), solve(xm + 1, xr, yl, yr, sque[1]);
    } else {
        int ym = (yl + yr) >> 1;
        for (int x = xl; x <= xr; x++) {
            Dijkstra(_(x, ym), xl, xr, yl, yr);
            for (auto i : ques) ans[get<2>(i)] = min(ans[get<2>(i)], dist[get<0>(i)] + dist[get<1>(i)]);
        }
        vector<tiii> sque[2];
        for (auto i : ques)
            if (($(get<0>(i)).second <= ym) == ($(get<1>(i)).second <= ym)) sque[$(get<0>(i)).second > ym].push_back(i);
        solve(xl, xr, yl, ym, sque[0]), solve(xl, xr, ym + 1, yr, sque[1]);
    }
    return;
}

void solve(void) {
    cin >> n >> m, graph.resize(_(n, m) + 1);
    for (int i = 1, v; i <= n; i++)
        for (int j = 1; j < m; j++)
            cin >> v, graph[_(i, j)].emplace_back(_(i, j + 1), v), graph[_(i, j + 1)].emplace_back(_(i, j), v);
    for (int i = 1, v; i < n; i++)
        for (int j = 1; j <= m; j++)
            cin >> v, graph[_(i, j)].emplace_back(_(i + 1, j), v), graph[_(i + 1, j)].emplace_back(_(i, j), v);
    int q;
    cin >> q;
    vector<tiii> ques;
    for (int i = 1, sx, sy, tx, ty; i <= q; i++)
        cin >> sx >> sy >> tx >> ty, ques.emplace_back(_(sx, sy), _(tx, ty), i), ans[i] = INT_MAX;
    solve(1, n, 1, m, ques);
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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