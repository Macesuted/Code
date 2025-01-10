/**
 * @file 105631H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int64_t f[1 << 11][12], qpow[12][12];
int cnt[1 << 11];
bool vis[25];
vector<int> graph[25];

void solve(void) {
    int n, m, r;
    cin >> n >> m >> r;
    for (int i = 1, x, y; i <= r; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    for (int S = 0; S < (1 << m); S++) {
        for (int i = 1; i <= n + m + 1; i++) vis[i] = false;
        queue<int> que;
        que.push(1), vis[1] = true;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            if (n + 2 <= p && !(S >> (p - (n + 2)) & 1)) continue;
            for (auto q : graph[p])
                if (!vis[q]) que.push(q), vis[q] = true;
        }
        for (int i = 2; i <= n + 1; i++) cnt[S] += vis[i];
    }

    if (cnt[0] == 0) return cout << 0 << endl, void();

    f[0][cnt[0]] = 1;

    for (int S = 0; S < ((1 << m) - 1); S++)
        for (int rS = ((1 << m) - 1) ^ S, T = rS; T; T = (T - 1) & rS) {
            int x = __builtin_popcount(T), t = cnt[S | T] - cnt[S];
            for (int i = 1; i <= n; i++)
                if (f[S][i]) f[S | T][t] += f[S][i] * qpow[i][x];
        }

    int64_t ans = 0;
    for (int i = 0; i <= n; i++) ans += f[((1 << m) - 1)][i];

    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int x = 1; x <= 11; x++) {
        qpow[x][0] = 1;
        for (int i = 1; i <= 11; i++) qpow[x][i] = qpow[x][i - 1] * x;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}