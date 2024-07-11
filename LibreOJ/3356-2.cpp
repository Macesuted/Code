/**
 * @file 3356.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-10
 *
 * @copyright Copyright (c) 2024
 * @brief
 *     O(n^(2/3) * q^(2/3) * k^(5/3))
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 50005
#define maxB 1005
#define maxk 5

typedef pair<int, int> pii;

vector<pii> graph[maxn], rgraph[maxn];
int bl[maxB], bel[maxn];
int64_t distL[maxk][maxn], distR[maxk][maxn], dist[maxB][maxB][maxk][maxk], distc[maxn];
queue<int> que;

void solve(void) {
    int K, n, m, q;
    cin >> K >> n >> m >> q;
    n = n / K + (n % K != 0) - 1;
    for (int i = 1, x, y, t; i <= m; i++) cin >> x >> y >> t, graph[x].emplace_back(y, t), rgraph[y].emplace_back(x, t);

    auto _ = [&](int x, int y) { return x * K + y; };

    int B = min(n, (int)max({1., n / 1000., pow((double)n * n * K / q, 1. / 3)})), bcnt = 0;
    bl[0] = 0;
    while (bl[bcnt] < n) bl[bcnt + 1] = bl[bcnt] + B, bcnt++;
    if (bl[bcnt] > n) bl[bcnt] = n;
    for (int i = 0; i < bcnt; i++)
        for (int j = bl[i]; j < bl[i + 1]; j++) bel[j] = i;
    bel[n] = bcnt;

    memset(distL, 0x3f, sizeof(distL)), memset(distR, 0x3f, sizeof(distR)), memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < bcnt; i++) {
        for (int o = 0; o < K; o++) {
            distL[o][_(bl[i], o)] = 0, que.push(_(bl[i], o));
            while (!que.empty()) {
                int p = que.front();
                que.pop();
                for (auto [t, v] : graph[p])
                    if (t < _(bl[i + 1], 0)) {
                        if (distL[o][t] == 0x3f3f3f3f3f3f3f3f) que.push(t);
                        distL[o][t] = min(distL[o][t], distL[o][p] + v);
                    }
            }
        }
        for (int o = 0; o < K; o++) {
            for (auto [t, v] : rgraph[_(bl[i + 1], o)]) distR[o][t] = v, que.push(t);
            while (!que.empty()) {
                int p = que.front();
                que.pop();
                for (auto [t, v] : rgraph[p])
                    if (t >= _(bl[i], 0)) {
                        if (distR[o][t] == 0x3f3f3f3f3f3f3f3f) que.push(t);
                        distR[o][t] = min(distR[o][t], distR[o][p] + v);
                    }
            }
        }
        for (int x = 0; x < K; x++)
            for (int y = 0; y < K; y++) dist[i][i + 1][x][y] = distR[y][_(bl[i], x)];
    }
    for (int i = 0; i < bcnt; i++)
        for (int j = i + 2; j <= bcnt; j++)
            for (int x = 0; x < K; x++)
                for (int y = 0; y < K; y++)
                    for (int z = 0; z < K; z++)
                        if (dist[i][j - 1][x][z] != 0x3f3f3f3f3f3f3f3f && dist[j - 1][j][z][y] != 0x3f3f3f3f3f3f3f3f)
                            dist[i][j][x][y] = min(dist[i][j][x][y], dist[i][j - 1][x][z] + dist[j - 1][j][z][y]);
    for (int i = 0; i <= bcnt; i++)
        for (int x = 0; x < K; x++) dist[i][i][x][x] = 0;
    for (int i = 0; i < K; i++) distL[i][_(n, i)] = 0;

    while (q--) {
        int a, b;
        cin >> a >> b;
        int na = a / K, nb = b / K, bela = bel[na], belb = bel[nb];
        if (bela == belb) {
            for (int i = a; i <= b; i++) distc[i] = INT64_MAX;
            distc[a] = 0;
            for (int i = a; i <= b; i++)
                if (distc[i] != INT64_MAX)
                    for (auto [t, v] : graph[i]) distc[t] = min(distc[t], distc[i] + v);
            cout << (distc[b] == INT64_MAX ? -1 : distc[b]) << endl;
            continue;
        }

        int64_t ans = INT64_MAX;
        for (int x = 0; x < K; x++)
            if (distR[x][a] != 0x3f3f3f3f3f3f3f3f)
                for (int y = 0; y < K; y++)
                    if (distL[y][b] != 0x3f3f3f3f3f3f3f3f && dist[bela + 1][belb][x][y] != 0x3f3f3f3f3f3f3f3f)
                        ans = min(ans, distR[x][a] + dist[bela + 1][belb][x][y] + distL[y][b]);

        cout << (ans == INT64_MAX ? -1 : ans) << endl;
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}