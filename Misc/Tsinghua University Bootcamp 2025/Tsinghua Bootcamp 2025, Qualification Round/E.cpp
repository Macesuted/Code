/**
 * @file E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-06-29
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

#define maxn 200010

int col[maxn], dis[4][maxn], pre[4][maxn], sum[maxn];
vector<int> graph[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int t = 1, c, x; t <= 3; t++) {
        cin >> c;
        while (c--) cin >> x, col[x] = t;
    }

    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if (col[x]) x = n + col[x];
        if (col[y]) y = n + col[y];
        graph[x].push_back(y), graph[y].push_back(x);
    }

    for (int t = 1; t <= 3; t++) {
        for (int i = 1; i <= n + 3; i++) dis[t][i] = 1e8, pre[t][i] = i;
        queue<int> que;
        dis[t][n + t] = 0, que.push(n + t);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto q : graph[p])
                if (dis[t][q] > dis[t][p] + 1) dis[t][q] = dis[t][p] + 1, pre[t][q] = p, que.push(q);
        }
    }

    for (int i = 1; i <= n + 3; i++) sum[i] = dis[1][i] + dis[2][i] + dis[3][i];
    int ansp = 1;
    for (int i = 1; i <= n + 3; i++)
        if (sum[i] < sum[ansp]) ansp = i;

    set<int> S;
    if (ansp <= n) S.insert(ansp);
    for (int t = 1; t <= 3; t++) {
        int p = pre[t][ansp];
        while (dis[t][p]) S.insert(p), p = pre[t][p];
    }

    cout << S.size() << endl;
    for (auto x : S) cout << x << ' ';
    cout << endl;

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
