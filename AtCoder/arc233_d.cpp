/**
 * @file arc233_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-28
 *
 * @copyright Copyright (c) 2026
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

int64_t fac[maxn], ifac[maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int64_t inv(int x) { return fac[x - 1] * ifac[x] % mod; }

void solve(void) {
    int A, B, K;
    cin >> A >> B >> K;

    int L = A + B;

    int64_t sum = 0, ans = 0;

    for (int i = 0; i <= min(A, max(L - K - 1, -1) / 2); i++) {
        int x = K + 2 * i, D = i, N = K + i;
        if (D > A || N > B) continue;

        int64_t prob = (int64_t)K * inv(x) % mod * C(x, D) % mod * C(L - x, A - D) % mod;
        sum = (sum + prob) % mod, ans = (ans + N * prob) % mod;
    }

    ans = (B + (ans + (int64_t)B * (mod - sum)) % mod * qpow(C(L, A), mod - 2)) % mod;

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
    ifac[maxn - 1] = qpow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
