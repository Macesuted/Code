/**
 * @file asaporo2_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

#define maxn 305
#define mod 1000000007

int d[maxn];
int64_t fac[maxn], ifac[maxn], f[maxn][maxn][2];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

void solve(void) {
    int n;
    cin >> n;
    bool chk = true;
    for (int i = 1; i <= n; i++) cin >> d[i], chk &= (d[i] == 2);
    if (chk) return cout << fac[n - 1] * Inv(2) % mod << endl, void();
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            f[i][j][0] = f[i - 1][j][0] * ifac[d[i] - 1] % mod, f[i][j][1] = f[i - 1][j][1] * ifac[d[i] - 1] % mod;
            if (j && d[i] > 1)
                f[i][j][0] = (f[i][j][0] + f[i - 1][j - 1][0] * ifac[d[i] - 2]) % mod,
                f[i][j][1] = (f[i][j][1] + f[i - 1][j - 1][1] * ifac[d[i] - 2]) % mod;
            if (j && d[i] > 2) f[i][j][1] = (f[i][j][1] + f[i - 1][j - 1][0] * ifac[d[i] - 3]) % mod;
        }
    int64_t ans = 0;
    for (int i = 3; i < n; i++) ans = (ans + f[n][i][1] * fac[n - i - 1] % mod * fac[i - 1] % mod * Inv(2)) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}