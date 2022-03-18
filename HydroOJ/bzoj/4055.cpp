/**
 * @file 4055.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, double> tid;

int a[maxn], n, m, dist[maxn][maxn];
long double f[maxn][maxn], g[maxn][maxn], R[maxn];
vector<tiii> rec;
bool vis[maxn];
vector<vector<tid>> graph;

void Dijkstra(int s) {
    for (int i = 1; i <= n; i++) vis[i] = false, dist[s][i] = numeric_limits<int>::max();
    static priority_queue<pii, vector<pii>, greater<pii>> que;
    while (!que.empty()) que.pop();
    que.emplace(dist[s][s] = 0, s);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[s][get<0>(i)] > dist[s][p] + get<1>(i))
                que.emplace(dist[s][get<0>(i)] = dist[s][p] + get<1>(i), get<0>(i));
    }
    return;
}

void solve(void) {
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        double d;
        cin >> x >> y >> c >> d;
        graph[x].emplace_back(y, c, d), graph[y].emplace_back(x, c, d);
    }
    for (int i = 1; i <= n; i++) Dijkstra(i);
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (i < get<0>(j) && dist[i][get<0>(j)] == get<1>(j))
                f[i][get<0>(j)] += get<2>(j);
    rec.reserve(n * (n - 1) / 2);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            rec.emplace_back(dist[i][j], i, j);
    sort(rec.begin(), rec.end());
    for (auto i : rec) {
        int dis = get<0>(i), p1 = get<1>(i), p2 = get<2>(i);
        for (auto e1 : graph[p1])
            for (auto e2 : graph[p2]) {
                int p3 = get<0>(e1), p4 = get<0>(e2);
                if (p3 > p4) swap(p3, p4);
                if (dis - get<1>(e1) - get<1>(e2) == dist[p3][p4])
                    f[p1][p2] += get<2>(e1) * get<2>(e2) * f[p3][p4];
            }
    }
    reverse(rec.begin(), rec.end());
    for (auto i : rec) {
        int dis = get<0>(i), p1 = get<1>(i), p2 = get<2>(i);
        g[p1][p2] += a[p1] * a[p2];
        for (auto e1 : graph[p1])
            for (auto e2 : graph[p2]) {
                int p3 = get<0>(e1), p4 = get<0>(e2);
                if (p3 > p4) swap(p3, p4);
                if (dis - get<1>(e1) - get<1>(e2) == dist[p3][p4]) {
                    long double t = g[p1][p2] * (f[p3][p4] * get<2>(e1) * get<2>(e2) / f[p1][p2]);
                    g[p3][p4] += t, R[p3] += t;
                    if (p3 != p4) R[p4] += t;
                }
            }
    }
    cout << setiosflags(ios::fixed) << setprecision(15);
    for (int i = 1; i <= n; i++) cout << R[i] * 2 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
