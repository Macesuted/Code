/**
 * @file 2091.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 17

int con[maxn][maxn], n, m;
int64_t f[maxn][maxn];
vector<int> graph[maxn];

void dfs(int p, int ban, int pre = -1) {
    for (int i = 0; i < n; i++) f[p][i] = 1;
    for (auto i : graph[p]) {
        if (i == pre) continue;
        dfs(i, ban, p);
        for (int x = 0; x < n; x++) {
            if (ban >> x & 1) continue;
            int64_t sum = 0;
            for (int y = 0; y < n; y++)
                if (!(ban >> y & 1) && con[x][y]) sum += f[i][y];
            f[p][x] *= sum;
        }
    }
    return;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, con[u - 1][v - 1] = con[v - 1][u - 1] = true;
    for (int i = 1, u, v; i < n; i++) cin >> u >> v, graph[u - 1].push_back(v - 1), graph[v - 1].push_back(u - 1);
    int64_t ans = 0;
    for (int S = 0; S < (1 << n); S++) {
        dfs(0, S);
        int64_t sum = 0;
        for (int i = 0; i < n; i++) sum += f[0][i];
        ans += ((__builtin_popcount(S) & 1) ? -1 : 1) * sum;
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