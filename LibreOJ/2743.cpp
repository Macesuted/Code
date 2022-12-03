/**
 * @file 2743.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-03
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
#define maxm 1005
#define mod 1000000007

int a[maxn], f[maxn][maxn][maxm][4];

int Mod(int x) { return x >= mod ? x - mod : x; }
int Add(int& x, int y) { return x = Mod(x + y); }

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (n == 1) return cout << 1 << endl, void();
    sort(a + 1, a + n + 1);
    f[1][1][0][0] = 1, f[1][1][0][1] = 2;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            for (int k = 0; k <= m; k++)
                for (int t = 0; t < 3; t++) {
                    int64_t v = f[i - 1][j][k][t], nk = k + (2 * j - t) * (a[i] - a[i - 1]);
                    if (nk > m) continue;
                    Add(f[i][j + 1][nk][t], v * (j + 1 - t) % mod);  // 新建块
                    Add(f[i][j][nk][t], v * (2 * j - t) % mod);      // 作为某块的左右端
                    Add(f[i][j - 1][nk][t], v * (j - 1) % mod);      // 连接两块
                    Add(f[i][j][nk][t + 1], v * (2 - t) % mod);      // 作为左右端，与某块连接
                    Add(f[i][j + 1][nk][t + 1], v * (2 - t) % mod);  // 作为左右端，新建块
                }
    int ans = 0;
    for (int v = 0; v <= m; v++) Add(ans, f[n][1][v][2]);
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