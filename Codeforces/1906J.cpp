/**
 * @file 1906J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 5005
#define mod 998244353

int a[maxn];
int64_t f[maxn][maxn], g[maxn][maxn], pow2[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    f[1][0] = g[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[i - 1] < a[i]) f[i][j] = f[i - 1][j];
            f[i][j] = (f[i][j] + g[i - 1][j - 1]) % mod;
            f[i][j] = f[i][j] * pow2[i - j - 1] % mod;
        }
        for (int j = 1; j < i; j++) g[i][j] = (g[i][j - 1] + f[i][j]) % mod;
    }
    cout << g[n][n - 1] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    int _ = 1;
    while (_--) solve();

    return 0;
}