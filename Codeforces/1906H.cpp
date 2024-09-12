/**
 * @file 1906H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int A[30], B[30];
int64_t fac[maxn], ifac[maxn], f[30][maxn];

int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    string SA, SB;
    cin >> SA >> SB;

    for (int i = 0; i < n; i++) A[SA[i] - 'A']++;
    for (int i = 0; i < m; i++) B[SB[i] - 'A']++;

    int64_t base = 1, sum = 0;
    for (int i = 0; i < 26; i++) sum += A[i], base = base * C(sum, A[i]) % mod;

    f[0][B[0]] = 1;
    for (int i = 1; i < 26; i++) {
        int64_t sum = 0;
        for (int j = B[i - 1]; j > A[i - 1]; j--) sum = (sum + f[i - 1][j]) % mod;
        for (int j = 0; j <= min(A[i - 1], B[i]); j++) {
            sum = (sum + f[i - 1][A[i - 1] - j]) % mod;
            f[i][B[i] - j] = sum * C(A[i - 1], j) % mod;
        }
    }
    int64_t ans = 0;
    for (int j = A[25]; j <= B[25]; j++) ans = (ans + f[25][j]) % mod;
    cout << ans * base % mod << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

    return 0;
}