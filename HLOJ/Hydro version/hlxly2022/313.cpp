/**
 * @file deepnest.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-09
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

#define maxn 105
#define maxv 40005

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;

int a[maxn];
int64_t dist[maxv];
bool vis[maxv];
vector<pii> graph[maxv];
priority_queue<pli, vector<pli>, greater<pli>> que;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << (a[1] == 1 ? "-1" : "INF") << endl;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < a[1]; j++) graph[j].emplace_back((j + a[i]) % a[1], a[i]), dist[j] = INT64_MAX, vis[j] = false;
        que.emplace(dist[0] = 0, 0);
        while (!que.empty()) {
            int p = que.top().second;
            que.pop();
            if (vis[p]) continue;
            vis[p] = true;
            for (auto i : graph[p])
                if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
        }
        int64_t maxd = 0;
        for (int j = 0; j < a[1]; j++) maxd = max(maxd, dist[j]);
        if (maxd == INT64_MAX)
            cout << "INF" << endl;
        else
            cout << maxd - a[1] << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("deepnest.in", "r", stdin), freopen("deepnest.out", "w", stdout);
#endif
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