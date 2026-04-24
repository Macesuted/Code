/**
 * @file 2206I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define maxlgn 20
#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t x) { return qpow(x, mod - 2); }

int a[maxn], d[maxn], lg2[maxn];
int f[maxn][maxlgn];
vector<int> chld[maxn];

int64_t fac[maxn], ifac[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }
int Add(int &x, int y) { return x = Mod(x + y); }
int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n - 1; i >= 1; i--) a[i] = min(a[i], a[i + 1]);

    for (int i = 2; i < maxn; i++) lg2[i] = lg2[i >> 1] + 1;

    for (int i = 1; i <= n; i++) d[a[i] + 1] = i;
    for (int i = 2; i <= a[n]; i++)
        if (!d[i]) d[i] = d[i - 1];

    for (int i = 1; i <= a[n]; i++)
        for (int j = 2 * i; j <= a[n]; j += i) chld[j].push_back(i);

    for (int i = 1; i <= a[n]; i++) {
        if (i <= a[1]) f[i][1] = 1;
        for (auto j : chld[i])
            for (int x = 0, dm = d[i] - d[j]; x <= min(dm, lg2[j] + 1); x++) {
                int64_t coef = C(dm, x);
                for (int y = max(0, 1 - x); x + y <= lg2[j] + 1; y++) {
                    if (i > a[1] && y == 0)
                        Add(f[i][1], C(dm - 1, x - 1) * f[j][x] % mod);
                    else
                        Add(f[i][y + 1], coef * f[j][x + y] % mod);
                }
            }
    }

    int ans = 0;

    for (int i = 1; i <= a[n]; i++)
        for (int j = 1, dm = n - d[i]; j <= min(dm, lg2[i] + 1); j++) Add(ans, C(dm - 1, j - 1) * f[i][j] % mod);

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