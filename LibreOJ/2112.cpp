/**
 * @file 2112.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 250
#define maxr 150

long double f[maxn], g[maxn][maxr], p[maxn], pd[maxn][maxr];
int d[maxn];

void solve(void) {
    int n, r;
    cin >> n >> r;
    for (int i = 1; i <= n; i++) cin >> p[i] >> d[i], p[i] = 1 - p[i];
    for (int i = 1; i <= n; i++) {
        pd[i][0] = 1;
        for (int j = 1; j <= r; j++) pd[i][j] = pd[i][j - 1] * p[i];
    }
    g[0][0] = 1;
    for (int i = 1; i <= n; i++) f[i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= min(r, i); j++) {
            g[i][j] = g[i - 1][j] * pd[i][r - j];
            if (j)
                g[i][j] += g[i - 1][j - 1] * (1 - pd[i][r - j + 1]), f[i] += g[i - 1][j - 1] * (1 - pd[i][r - j + 1]);
        }
    long double ans = 0;
    for (int i = 1; i <= n; i++) ans += f[i] * d[i];
    cout << fixed << setprecision(10) << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
