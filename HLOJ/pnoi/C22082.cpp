/**
 * @file C22082.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-23
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

#define maxn 1000005
#define maxv 3000005
#define mod 998244353

int64_t fac[maxv], ifac[maxv], inv[maxv];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int64_t Mod(int64_t a) { return a >= mod ? a - mod : a; }

void solve(void) {
    int A, B;
    cin >> A >> B;
    int64_t ans = 0;
    for (int i = 1; i <= B; i++) ans = Mod(ans + inv[2 * A + i]);
    for (int i = 0; i < A; i++) ans = Mod(ans + inv[2 * i + 1]);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("string.in", "r", stdin), freopen("string.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxv; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxv - 1] = Inv(fac[maxv - 1]);
    for (int i = maxv - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxv; i++) inv[i] = ifac[i] * fac[i - 1] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}