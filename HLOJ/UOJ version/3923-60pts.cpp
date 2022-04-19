/**
 * @file eeswes.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 6000005
#define mod 998244353

vector<int> prime;
bool notp[maxn];
int64_t phi[maxn], mu[maxn], sig[maxn], lp[maxn], fac[maxn], ifac[maxn], inv[maxn];

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
    int64_t ans = 0;
    for (int j = 1; j <= n; j++)
        for (int d = 1; d <= n; d++) {
            int64_t p1 = 0, p2 = 0;
            for (int i = d; i <= n; i += d) p1 = (p1 + phi[i * j] * mu[i]) % mod;
            for (int k = d; k <= n; k += d) p2 = (p2 + sig[j * k] * mu[k]) % mod;
            ans = (ans + mu[d] * p1 % mod * p2) % mod;
        }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("eeswes.in", "r", stdin), freopen("eeswes.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxn; i++) inv[i] = ifac[i] * fac[i - 1] % mod;

    phi[1] = mu[1] = sig[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!notp[i]) prime.push_back(i), phi[i] = i - 1, mu[i] = mod - 1, lp[i] = sig[i] = 2;
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            int x = i * *j;
            notp[x] = true;
            if (i % *j == 0) {
                phi[x] = phi[i] * *j % mod, mu[x] = 0, sig[x] = sig[i] * inv[lp[i]] % mod * (lp[x] = lp[i] + 1) % mod;
                break;
            }
            phi[x] = phi[i] * phi[*j] % mod, mu[x] = (mod - mu[i]) % mod, sig[x] = sig[i] * (lp[x] = 2);
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
