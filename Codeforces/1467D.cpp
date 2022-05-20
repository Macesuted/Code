/**
 * @file 1467D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 5005
#define mod 1000000007

int64_t f[maxn][maxn], g[maxn], a[maxn];

void solve(void) {
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], f[0][i] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= n; j++) f[i][j] = (f[i - 1][j - 1] + f[i - 1][j + 1]) % mod;
    for (int i = 0; i <= k; i++)
        for (int j = 1; j <= n; j++) g[j] = (g[j] + f[i][j] * f[k - i][j]) % mod;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + g[i] * a[i]) % mod;
    while (q--) {
        int p, x;
        cin >> p >> x;
        ans = (ans + (x + mod - a[p]) * g[p]) % mod, a[p] = x;
        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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