/**
 * @file 6710.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using namespace std;

#define maxn 32

long long f[maxn << 1][maxn][maxn][maxn], finv2[maxn * maxn], fac[maxn], ifac[maxn], mod;

long long qpow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
long long inv(long long a) { return qpow(a, mod - 2); }
long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, m;
    cin >> n >> m >> mod, m--;

    finv2[0] = fac[0] = ifac[0] = 1, finv2[1] = inv(2);
    for (int i = 2; i <= n * m; i++) finv2[i] = finv2[i - 1] * finv2[1] % mod;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    long long ans = 0;
    f[0][0][0][1] = 1;
    for (int d = 1; d <= n + m; d++) {
        for (int l1 = 0; l1 <= m; l1++)
            for (int r1 = 0; r1 <= n; r1++)
                for (int l2 = 1; l1 + l2 <= m; l2++) f[d][l1][r1][l2] = 0;
        for (int l1 = 0; l1 <= n; l1++)
            for (int r1 = 0; r1 <= m; r1++)
                for (int l2 = 1; l1 + l2 <= n; l2++)
                    if (f[d - 1][l1][r1][l2])
                        for (int r2 = 1; r1 + r2 <= m; r2++)
                            f[d][r1][l1 + l2][r2] =
                                (f[d][r1][l1 + l2][r2] + f[d - 1][l1][r1][l2] * C(m - r1, r2) % mod *
                                                             finv2[l2 * (m - r1 - r2)] % mod * qpow(mod + 1 - finv2[l2], r2)) %
                                mod;
        if (d & 1) {
            long long sum = 0;
            for (int l1 = 0; l1 <= n; l1++)
                for (int r1 = 0; r1 <= m; r1++)
                    for (int l2 = 1; l1 + l2 <= n; l2++)
                        if (f[d - 1][l1][r1][l2])
                            sum = (sum + f[d - 1][l1][r1][l2] * finv2[l1] % mod * (mod + 1 - finv2[l2])) % mod;
            ans = (ans + sum * d) % mod;
        }
        swap(n, m);
    }
    cout << ans << endl;
    return;
}

int main() {
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}