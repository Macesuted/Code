/**
 * @file arc202_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

#define mod 998244353
#define maxn 200005

bool mem1;

int64_t v[maxn], mu[maxn], pow10[maxn], invf[maxn], phi[maxn];
int a[maxn];
bool vis[maxn];

bool notp[maxn];
vector<int> primes;
int lstp[maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vis[1] = true;
    int64_t ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= a[i]; j++)
            if (a[i] % j == 0) {
                int v = a[i] / j;
                if (!vis[j]) vis[j] = true, ans = ans * phi[j] % mod;
                if (!vis[v]) vis[v] = true, ans = ans * phi[v] % mod;
            }
        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    v[0] = pow10[0] = 1;
    for (int i = 1; i < maxn; i++) v[i] = (v[i - 1] * 10 + 1) % mod, pow10[i] = pow10[i - 1] * 10 % mod;
    for (int i = 0; i < maxn; i++) invf[i] = inv((pow10[i] + mod - 1) % mod);

    mu[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!notp[i]) primes.push_back(i), lstp[i] = i, mu[i] = -1;
        for (auto j = primes.begin(); i * *j < maxn; j++) {
            notp[i * *j] = true, lstp[i * *j] = *j;
            if (i % *j == 0) {
                mu[i * *j] = 0;
                break;
            }
            mu[i * *j] = -mu[i];
        }
    }

    for (int i = 1; i < maxn; i++) {
        phi[i] = 1;
        for (int j = 1; j * j <= i; j++)
            if (i % j == 0) {
                int v = i / j;
                if (mu[j] == -1) phi[i] = phi[i] * invf[v] % mod;
                if (mu[j] == +1) phi[i] = phi[i] * (pow10[v] + mod - 1) % mod;
                if (v == j) continue;
                if (mu[v] == -1) phi[i] = phi[i] * invf[j] % mod;
                if (mu[v] == +1) phi[i] = phi[i] * (pow10[j] + mod - 1) % mod;
            }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}