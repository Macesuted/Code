/**
 * @file 2728.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 4005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int n, m, L;
bool ban[maxn][maxn];
int f[2][maxn][maxn], g[2][maxn][maxn];
queue<int> pos[maxn];

int solve(int sx, int sy) {
    int ans = 0;
    for (int x = sx, tx = x + L - 1, y = sy, ty = y + L - 1; x && y; x--, y--, tx--, ty--) {
        if (tx <= n && ty <= m && tx - g[0][tx][ty] <= x) FT.add(tx, +1), pos[tx - g[0][tx][ty]].push(tx);
        ans += FT.sum(x + f[0][x][y]);
        while (!pos[x].empty()) FT.add(pos[x].front(), -1), pos[x].pop();
    }
    return ans;
}

void solve(void) {
    int q;
    cin >> n >> m >> L >> q;
    for (int i = 1, x, y; i <= q; i++) cin >> x >> y, ban[x][y] = true;
    for (int i = 1; i <= n; i++)
        for (int j = m - 1; j; j--) f[0][i][j] = (ban[i][j] ? -1 : f[0][i][j + 1] + 1);
    for (int j = 1; j <= m; j++)
        for (int i = n - 1; i; i--) f[1][i][j] = (ban[i][j] ? -1 : f[1][i + 1][j] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= m; j++) g[0][i][j] = (ban[i][j] ? -1 : g[0][i][j - 1] + 1);
    for (int j = 1; j <= m; j++)
        for (int i = 2; i <= n; i++) g[1][i][j] = (ban[i][j] ? -1 : g[1][i - 1][j] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) f[0][i][j] = min(f[0][i][j], f[1][i][j]), g[0][i][j] = min(g[0][i][j], g[1][i][j]);
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += solve(i, m);
    for (int i = 1; i < m; i++) ans += solve(n, i);
    return cout << ans << endl, void();
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