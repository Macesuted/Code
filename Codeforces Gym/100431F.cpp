/**
 * @file 100431F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

#define maxn 305
#define mod 1'000'000'007

int64_t f[maxn][maxn], C[maxn][maxn];
int a[maxn], pre[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    pre[0] = 0;
    for (int i = 1; i <= k; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];

    f[1][1] = 1;
    for (int i = 1; i < k; i++)
        for (int j = 1; j <= pre[i]; j++) {
            if (!f[i][j]) continue;
            for (int nj = 1; nj <= pre[i] + 1; nj++) {
                f[i + 1][nj] = (f[i + 1][nj] + C[pre[i + 1] - nj][a[i + 1] - 1] * f[i][j]) % mod;
                if (j >= nj) f[i + 1][nj] = (f[i + 1][nj] + mod - C[j - 1 + a[i + 1] - nj][a[i + 1] - 1] * f[i][j] % mod) % mod;
            }
        }

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + f[k][i]) % mod;
    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("monotonic.in", "r", stdin), freopen("monotonic.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}