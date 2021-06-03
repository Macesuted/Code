/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353
#define maxn 200005

long long fac[maxn], inv[maxn];

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

inline long long C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
void INIT(void) {
    fac[0] = inv[0] = 1;
    for (register int i = 1; i < maxn; i++) fac[i] = fac[i - 1] % mod;
    inv[maxn - 1] = power(fac[maxn - 1], mod - 2);
    for (register int i = maxn - 2; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    return;
}

int a[maxn], f[maxn][35];

int n, k;

void work(void) {
    // INIT();
    cin >> n >> k;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j < 35; j++) {
            f[i][j] = f[i - 1][j] + 1;
            if (j) f[i][j] = min(f[i][j], f[upper_bound(a + 1, a + n + 1, a[i] / 2) - 1 - a][j - 1]);
        }
    for (register int j = 0; j < 35; j++)
        if (f[n][j] <= k) {
            cout << j << ' ' << f[n][j] << endl;
            return;
        }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(3) << endl;
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}