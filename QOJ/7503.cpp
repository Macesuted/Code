/**
 * @file 7503.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 50005

vector<int> graph[maxn];
int indeg[maxn], dist[maxn], pre[maxn];

bool query(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y);

    while (true) {
        for (int i = 1; i <= n; i++) indeg[i] = 0;
        for (int i = 1; i <= n; i++)
            for (auto j : graph[i]) indeg[j]++;

        queue<int> que;
        for (int i = 1; i <= n; i++)
            if (!indeg[i]) que.push(i), dist[i] = 0, pre[i] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto q : graph[p])
                if (!--indeg[q]) dist[q] = dist[p] + 1, pre[q] = p, que.push(q);
        }

        int ep = 1;
        for (int i = 1; i <= n; i++)
            if (dist[i] > dist[ep]) ep = i;

        vector<int> path;
        while (ep) path.push_back(ep), ep = pre[ep];
        reverse(path.begin(), path.end());

        bool chk = true;
        for (size_t i = 1; i < path.size(); i++)
            if (!query(path[i - 1], path[i])) {
                chk = false;
                graph[path[i - 1]].erase(find(graph[path[i - 1]].begin(), graph[path[i - 1]].end(), path[i]));
                break;
            }
        if (chk) return cout << "! " << path.size() - 1 << endl, void();
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