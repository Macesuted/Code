/**
 * @file 100201H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-09
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

#define maxn 105

typedef tuple<int, int, int> tiii;

int stat[maxn][maxn], ch[maxn][maxn], jmp[maxn][maxn];
bool vis[maxn][maxn][2];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> stat[i][j] >> ch[i][j] >> jmp[i][j];

    queue<tiii> que;
    for (int j = 1; j <= m; j++) que.emplace(1, j, j == m), vis[1][j][j == m] = true;
    while (!que.empty()) {
        auto [p, c, sp] = que.front();
        que.pop();
        if (p == n) continue;
        if (jmp[p][c] == -1) return cout << "NO" << endl, void();
        if (jmp[p][c] == 0) {
            if (!vis[stat[p][c]][ch[p][c]][sp]) que.emplace(stat[p][c], ch[p][c], sp), vis[stat[p][c]][ch[p][c]][sp] = true;
            continue;
        }
        for (int j = (sp ? m : 1); j <= m; j++)
            if (!vis[stat[p][c]][j][j == m]) que.emplace(stat[p][c], j, j == m), vis[stat[p][c]][j][j == m] = true;
    }

    return cout << "YES" << endl, void();
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("left.in", "r", stdin), freopen("left.out", "w", stdout);
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