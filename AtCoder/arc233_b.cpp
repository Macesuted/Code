/**
 * @file arc233_b.cpp
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

#define maxn 200005
#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int a[maxn];
int64_t fac[maxn], ifac[maxn];

int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int64_t ans = 1;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;

        int cnt = 0;
        unordered_map<int, int> S;
        S[a[l]]++;
        while (r + 1 <= n && (a[r + 1] % k == a[l] % k || (a[r + 1] + a[l]) % k == 0))
            S[a[++r]]++, cnt += ((a[l] + a[r]) % k == 0);

        int64_t rest = r - l + 1;
        if (a[l] * 2 % k == 0)
            for (auto [v, c] : S) ans = ans * C(rest, c) % mod, rest -= c;
        else
            ans = ans * C(rest, cnt) % mod;
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
