/**
 * @file 105586B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

const int way[8][2] = {{+1, -2}, {+2, -1}, {+2, +1}, {+1, +2}, {-1, +2}, {-2, +1}, {-2, -1}, {-1, -2}};

int dis[20000005], f[20000005];
bool vis[20000005];

typedef pair<int, int> pii;

void solve(void) {
    int n, m;
    cin >> n >> m;

    auto _ = [&](int x, int y, int t) { return (x + 5) + (y + 5) * (n + 11) + t * (n + 11) * (m + 11); };
    auto $ = [&](int x, int y) { return (x + 5) + (y + 5) * (n + 11); };

    for (int i = 0; i <= _(n + 5, m + 5, 7); i++) f[i] = dis[i] = 1e8, vis[i] = false;

    {
        queue<int> que;
        que.push($(0, 0)), dis[$(0, 0)] = 0;
        while (!que.empty()) {
            int id = que.front();
            que.pop();
            int x = id % (n + 11) - 5, y = id / (n + 11) % (m + 11) - 5;
            for (int i = 0; i < 8; i++) {
                int tx = x + way[i][0], ty = y + way[i][1], nid = $(tx, ty);
                if (tx < -5 || tx > n + 5 || ty < -5 || ty > m + 5) continue;
                if (dis[nid] > dis[id] + 1) dis[nid] = dis[id] + 1, que.push(nid);
            }
        }
    }

    priority_queue<pii, vector<pii>, greater<pii>> que;
    for (int t = 0; t < 8; t++)
        que.emplace(f[_(way[t][0], way[t][1], t)] = dis[$(n - way[t][0], m - way[t][1])], _(way[t][0], way[t][1], t));
    while (!que.empty()) {
        auto [d, id] = que.top();
        que.pop();
        int x = id % (n + 11) - 5, y = id / (n + 11) % (m + 11) - 5, t = id / ((n + 11) * (m + 11));
        if (vis[id]) continue;
        vis[id] = true;
        for (int i = 0; i < 8; i++) {
            int tx = x + way[i][0], ty = y + way[i][1], d = (i == t ? 5 : 3), nid = _(tx, ty, i);
            if (tx < -5 || tx > n + 5 || ty < -5 || ty > m + 5) continue;
            if (f[nid] > f[id] + d) que.emplace(f[nid] = f[id] + d, nid);
        }
    }

    int ans = INT_MAX;
    for (int t = 0; t < 8; t++) ans = min(ans, f[_(n, m, t)]);
    cout << ans + 1 << endl;

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