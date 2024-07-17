/**
 * @file 535265B.cpp
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

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int64_t C[maxn][maxn], f[maxn], pow2[maxn];

int main() {

    int n, m;
    cin >> n >> m >> mod;

    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    for (int i = 0; i <= max(n, m); i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    for (int i = 1; i <= n; i++)
        for (int j = i, x = 1; j >= 0; j--, x = -x)
            f[i] = (f[i] + x * C[i][j] * qpow(pow2[i] - 1 - (i - j), m - 1)) % mod;

    int64_t ans = 0;
    for (int t = 2; t <= n; t++)
        ans = (ans + (qpow(pow2[t] - 1, m - 1) + mod - f[t]) * qpow(2, (n - t) * (m - 1)) % mod * C[n][t]) % mod;
    cout << (ans + mod) % mod << endl;

    return 0;
}