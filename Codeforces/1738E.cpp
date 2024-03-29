/**
 * @file 1738E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-30
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

#define maxn 100005
#define mod 998244353

int a[maxn], f[maxn];
int64_t sum[maxn], fac[maxn], ifac[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t getSum(int l, int r) { return sum[r] - sum[l - 1]; }
int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];
    int64_t ans = 1;
    int lasi = 0, lasj = n + 1;
    for (int i = 1, j = n; i < j; i++) {
        while (getSum(1, i) > getSum(j, n)) j--;
        if (getSum(1, i) != getSum(j, n)) continue;
        if (i >= j) continue;
        if (!getSum(lasi + 1, i)) continue;
        int lenl = 0, lenr = 0;
        while (a[lasi + lenl + 1] == 0) lenl++;
        while (a[lasj - lenr - 1] == 0) lenr++;
        if (!lasi) lenl--, lenr--, ans = ans * 2 % mod;
        int64_t sum = 1;
        for (int i = 1; i <= min(lenl, lenr) + 1; i++) sum = (sum + binom(lenl + 1, i) * binom(lenr + 1, i)) % mod;
        ans = ans * sum % mod;
        lasi = i, lasj = j;
    }
    if (!getSum(lasi + 1, lasj - 1))
        ans = ans * Pow(2, lasj - 1 - lasi - (!lasi)) % mod;
    else {
        int lenl = 0, lenr = 0;
        while (a[lasi + lenl + 1] == 0) lenl++;
        while (a[lasj - lenr - 1] == 0) lenr++;
        if (!lasi) lenl--, lenr--, ans = ans * 2 % mod;
        int64_t sum = 1;
        for (int i = 1; i <= min(lenl, lenr) + 1; i++) sum = (sum + binom(lenl + 1, i) * binom(lenr + 1, i)) % mod;
        ans = ans * sum % mod * Inv(2) % mod;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}