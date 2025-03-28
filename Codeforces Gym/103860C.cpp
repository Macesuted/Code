/**
 * @file 103860C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define mod 998'244'353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int64_t fac[maxn], ifac[maxn];
int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) cin >> a[i];

    int64_t ans = 1;
    for (int i = 1; i < n; i++) ans = ans * C(a[i + 1] + 1, a[i]) % mod;
    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

    return 0;
}