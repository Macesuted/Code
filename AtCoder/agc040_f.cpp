/**
 * @file agc040_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-07
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

#define maxn 10000005
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t fac[maxn], ifac[maxn];

int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int64_t catalan(int n, int m) {
    int64_t ans = binom(n + m - 1, m);
    if (m) ans = (ans + mod - binom(n + m - 1, n)) % mod;
    return ans;
}

void solve(void) {
    int n, a, b;
    cin >> n >> a >> b;
    if (b == 0) return cout << 1 << endl, void();
    int64_t ans = 0;
    for (int i = 0; i <= min(a, n - b); i++) {
        int j = n - b - i, v = a - i + 1;
        if (j == 0) {
            if (a == i) ans = (ans + catalan(b, i)) % mod;
        } else
            ans = (ans + catalan(b, i) * binom(j + v - 2, j - 1)) % mod;
    }
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