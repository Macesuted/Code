/**
 * @file 535265A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 5005

int mod;

int C[maxn][maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m >> mod;

    for (int i = 0; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    int64_t ans = 0;
    for (int t = 1; t <= n; t++) ans = (ans + qpow(qpow(2, t) - 1, m - 1) * qpow(2, (n - t) * (m - 1)) % mod * C[n][t]) % mod;
    cout << ans << endl;

    return 0;
}