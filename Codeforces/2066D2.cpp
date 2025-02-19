/**
 * @file 2066D2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 105
#define maxm 10005
#define mod 1'000'000'007

int a[maxm], pre[maxm], cnt[maxn], lst[maxn], f[maxn][maxm];
int64_t fac[maxm], ifac[maxm];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }
int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, c, m;
    cin >> n >> c >> m;

    for (int i = 1; i <= n; i++) cnt[i] = lst[i] = 0;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        if (a[i]) cnt[a[i]]++, lst[a[i]] = i;
    }

    if (cnt[n] > c) return cout << 0 << endl, void();

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) f[i][j] = 0;

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) pre[j] = pre[j - 1] + (a[j] <= i);
        for (int j = 0; j <= m; j++)
            if (f[i - 1][j])
                for (int k = (i == n ? c : cnt[i]); k <= c; k++)
                    if (lst[i] <= c + j && j + k <= m && k <= pre[min(m, c + j)] - j)
                        f[i][j + k] = (f[i][j + k] + f[i - 1][j] * C(pre[min(m, c + j)] - j - cnt[i], k - cnt[i])) % mod;
    }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j <= m; j++) cerr << f[i][j] << ' ';
    //     cerr << endl;
    // }

    cout << f[n][m] << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxm; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxm - 1] = inv(fac[maxm - 1]);
    for (int i = maxm - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}