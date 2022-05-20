/**
 * @file 660E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1000005
#define mod 1000000007

int64_t fac[maxn], ifac[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    if (m == 1) return cout << n + 1 << endl, void();
    int64_t ans = Pow(m, n), invm = Pow(m - 1, mod - 2), pw1 = 1, pw2 = Pow(m - 1, n);
    for (int i = 1; i <= n; i++)
        pw1 = pw1 * m % mod, pw2 = pw2 * invm % mod, ans = (ans + pw1 * pw2 % mod * binom(n, n - i + 1)) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}