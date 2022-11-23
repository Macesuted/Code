/**
 * @file C22081.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-23
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

#define maxn 505

typedef pair<int, int> pii;

bool D[maxn][maxn], R[maxn][maxn], vis[maxn][maxn];
int bel[maxn][maxn];
queue<pii> que;
set<int> S;
int n, m, lR, rR, lC, rC, cnt;

void bfs(int x, int y) {
    que.emplace(x, y), vis[x][y] = true;
    while (!que.empty()) {
        int x, y;
        tie(x, y) = que.front(), que.pop(), lR = min(lR, x), rR = max(rR, x), lC = min(lC, y), rC = max(rC, y), cnt++;
        if (x > 1 && D[x - 1][y] && !vis[x - 1][y]) que.emplace(x - 1, y), vis[x - 1][y] = true;
        if (x < n && D[x][y] && !vis[x + 1][y]) que.emplace(x + 1, y), vis[x + 1][y] = true;
        if (y > 1 && R[x][y - 1] && !vis[x][y - 1]) que.emplace(x, y - 1), vis[x][y - 1] = true;
        if (y < m && R[x][y] && !vis[x][y + 1]) que.emplace(x, y + 1), vis[x][y + 1] = true;
    }
    return;
}
void solve(void) {
    string s;
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        for (int j = 1; j < m; j++) R[i][j] = (s[j * 2] != '|');
        cin >> s;
        for (int j = 1; j <= m; j++) D[i][j] = (s[j * 2 - 1] != '-');
    }
    int bcnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (bel[i][j]) continue;
            lR = lC = INT_MAX, rR = rC = INT_MIN, cnt = 0, bfs(i, j);
            while ((rR - lR + 1) * (rC - lC + 1) > cnt) {
                for (int i = lR; i <= rR; i++)
                    for (int j = lC; j <= rC; j++)
                        if (!vis[i][j]) bfs(i, j);
            }
            bcnt++;
            for (int i = lR; i <= rR; i++)
                for (int j = lC; j <= rC; j++) vis[i][j] = false, bel[i][j] = bcnt;
            for (int i = lR; i <= rR; i++)
                for (int j = lC; j < rC; j++) R[i][j] = true;
            for (int i = lR; i < rR; i++)
                for (int j = lC; j <= rC; j++) D[i][j] = true;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) S.insert(bel[i][j]);
    cout << S.size() << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("field.in", "r", stdin), freopen("field.out", "w", stdout);
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