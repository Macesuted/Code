/**
 * @file 6040.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 2005
#define mod 1000000007

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

bitset<maxn> a[maxn];
int64_t f[maxn][maxn], pow2[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            bool t;
            cin >> t, a[i][j] = t;
        }
    int r = 0;
    for (int i = 1; i <= n; i++) {
        int p = 0;
        for (int j = r + 1; j <= n; j++)
            if (a[j][i]) p = j;
        if (!p) continue;
        swap(a[++r], a[p]);
        for (int j = 1; j <= n; j++)
            if (r != j && a[j][i]) a[j] ^= a[r];
    }
    f[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            f[i + 1][j] = (f[i + 1][j] + f[i][j] * pow2[j]) % mod,
                  f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] * (pow2[n] + mod - pow2[j])) % mod;
    int64_t ans = 0;
    for (int i = r; i <= n; i++) ans = (ans + f[n][i] * f[i][r] % mod * Pow(pow2[n - i], n)) % mod;
    cout << ans * Inv(f[n][r]) % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}