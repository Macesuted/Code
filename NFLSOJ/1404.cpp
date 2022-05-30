/**
 * @file 1404.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 50005
#define maxsqrtn 300

typedef pair<int, int> pii;

int L[maxsqrtn], R[maxsqrtn], bel[maxn], udist[maxn][5], ddist[maxn][5], dist[maxn];
vector<pii> graph[maxn], revg[maxn];

void solve(void) {
    int k, n, m, o;
    cin >> k >> n >> m >> o;
    n = n / k + (n % k > 0);
    int B = sqrt(n), cntB = n / B;
    L[0] = 0, R[0] = B - 1;
    for (int i = 1; i < cntB; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + B;
    if (R[cntB - 1] < n - 1) L[cntB] = R[cntB - 1] + 1, R[cntB] = n - 1, cntB++;
    for (int i = 0; i < cntB; i++)
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
    for (int i = 1, a, b, t; i <= m; i++) cin >> a >> b >> t, graph[a].emplace_back(b, t), revg[b].emplace_back(a, t);
    memset(udist, 0x3f, sizeof(udist)), memset(ddist, 0x3f, sizeof(ddist));
    for (int b = 0; b < cntB; b++) {
        for (int t = 0; t < k; t++) {
            udist[L[b] * k + t][t] = 0;
            for (int i = L[b]; i < R[b]; i++)
                for (int j = i * k; j < (i + 1) * k; j++)
                    for (auto e : graph[j]) udist[e.first][t] = min(udist[e.first][t], udist[j][t] + e.second);
        }
        for (int t = 0; t < k; t++) {
            ddist[R[b] * k + t][t] = 0;
            for (int i = R[b]; i > L[b]; i--)
                for (int j = i * k; j < (i + 1) * k; j++)
                    for (auto e : revg[j]) ddist[e.first][t] = min(ddist[e.first][t], ddist[j][t] + e.second);
        }
    }
    while (o--) {
        int x, y;
        cin >> x >> y;
        int dx = x / k, dy = y / k, blx = bel[dx], bly = bel[dy];
        if (blx == bly) {
            for (int i = dx * k; i < (dy + 1) * k; i++) dist[i] = 0x3f3f3f3f;
            dist[x] = 0;
            for (int i = dx; i < dy; i++)
                for (int j = i * k; j < (i + 1) * k; j++)
                    for (auto e : graph[j]) dist[e.first] = min(dist[e.first], dist[j] + e.second);
        } else {
            for (int i = blx; i <= bly; i++)
                for (int j = 0; j < k; j++) dist[L[i] * k + j] = dist[R[i] * k + j] = 0x3f3f3f3f;
            dist[y] = 0x3f3f3f3f;
            for (int i = 0; i < k; i++) dist[R[blx] * k + i] = ddist[x][i];
            for (int j = R[blx] * k; j < (R[blx] + 1) * k; j++)
                for (auto e : graph[j]) dist[e.first] = min(dist[e.first], dist[j] + e.second);
            for (int i = blx + 1; i < bly; i++) {
                for (int j = L[i] * k; j < (L[i] + 1) * k; j++)
                    for (int e = 0; e < k; e++) dist[R[i] * k + e] = min(dist[R[i] * k + e], dist[j] + ddist[j][e]);
                for (int j = R[i] * k; j < (R[i] + 1) * k; j++)
                    for (auto e : graph[j]) dist[e.first] = min(dist[e.first], dist[j] + e.second);
            }
            for (int i = 0; i < k; i++) dist[y] = min(dist[y], dist[L[bly] * k + i] + udist[y][i]);
        }
        cout << (dist[y] == 0x3f3f3f3f ? -1 : dist[y]) << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    freopen("toll.in", "r", stdin), freopen("toll.out", "w", stdout);
#endif
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