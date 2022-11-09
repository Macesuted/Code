/**
 * @file 4220.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
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

#define maxn 100005

typedef pair<int, int64_t> piI;

vector<piI> graph[3][maxn];
int64_t dep[3][maxn];
bool vis[maxn];

void dfs(int t, int p, int pre = -1) {
    for (auto i : graph[t][p])
        if (i.first != pre) dep[t][i.first] = dep[t][p] + i.second, dfs(t, i.first, p);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int t = 0; t < 3; t++)
        for (int i = 1, x, y; i < n; i++) {
            int64_t w;
            cin >> x >> y >> w, graph[t][x].emplace_back(y, w), graph[t][y].emplace_back(x, w);
        }
    mt19937 rnd(114514);
    int64_t ans = 0;
    int root = rnd() % n + 1, cnt = 0, las = 0;
    while (cnt < n && clock() * 1000. / CLOCKS_PER_SEC <= 3900) {
        if (las > 10) root = rnd() % n + 1, las = 0;
        while (vis[root]) root = rnd() % n + 1;
        vis[root] = true, cnt++, las++;
        int64_t far = 0;
        for (int t = 0; t < 3; t++) dep[t][root] = 0, dfs(t, root);
        for (int i = 1; i <= n; i++) {
            int64_t v = dep[0][i] + dep[1][i] + dep[2][i];
            ans = max(ans, v), far = max(far, v);
            if (far == v && !vis[i]) root = i;
        }
    }
    cout << ans << endl;
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