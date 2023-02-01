/**
 * @file 101.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 40000005
#define mod 998244353

int64_t fac[maxn], ifac[maxn], fac2[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, a, b;
    cin >> n >> a >> b;
    if (((n + a + b) & 1) || n < abs(a - b)) return cout << 0 << endl, void();
    int64_t ans = 0;
    for (int i = 0, f = 1; i * 2 <= a; i++, f = mod - f)
        ans = (ans + f * binom(a, 2 * i) % mod * (i == 0 ? 1 : fac2[2 * i - 1]) % mod * fac[n + a - 2 * i] % mod *
                         ifac[n + a - 2 * i - b] % mod * fac2[n + a - 2 * i - b - 1]) %
              mod;
    cout << ans * ifac[a] % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("fa.in", "r", stdin), freopen("fa.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = fac[1] = ifac[0] = fac2[0] = fac2[1] = 1;
    for (int i = 2; i < maxn; i++) fac[i] = fac[i - 1] * i % mod, fac2[i] = fac2[i - 2] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}