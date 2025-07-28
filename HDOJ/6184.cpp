/**
 * @file 6184.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

#define maxn 100005

vector<vector<int>> graph, ques;

bool mark[maxn];

void solve(void) {
    int n, m;
    while (cin >> n >> m) {
        graph.clear(), graph.resize(n + 1);
        for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

        ques.clear(), ques.resize(n + 1);
        for (int p = 1; p <= n; p++)
            for (auto q : graph[p])
                if (p < q) graph[p].size() > graph[q].size() ? ques[p].push_back(q) : ques[q].push_back(p);

        int64_t ans = 0;
        for (int p = 1; p <= n; p++) {
            for (auto q : graph[p]) mark[q] = true;

            for (auto q : ques[p]) {
                int cnt = 0;
                for (auto x : graph[q]) cnt += mark[x];
                ans += int64_t(cnt) * (cnt - 1) / 2;
            }

            for (auto q : graph[p]) mark[q] = false;
        }

        cout << ans << endl;
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