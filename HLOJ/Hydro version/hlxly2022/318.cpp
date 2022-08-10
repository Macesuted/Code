/**
 * @file 318.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-10
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

#define maxn 1005
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
int64_t Mod(int64_t a) { return a >= mod ? a - mod : a; }

int a[maxn], f[maxn][maxn], g[maxn][maxn];

void solve(void) {
    int n, cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt += (a[i] == -1);
    reverse(a + 1, a + n + 1);
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        f[i + 1][0] = g[i][0] = 1;
        for (int j = i; j; j--) {
            for (int k = 0; k * 2 <= i - j + 1; k++) f[j][k] = 0;
            for (int k = 0; k * 2 <= i - j; k++) {
                if (a[j] != 1 && (k + 1) * 2 <= i - j + 1) f[j][k + 1] = Mod(f[j][k + 1] + f[j + 1][k]);
                if (a[j] != 0) f[j][k] = Mod(f[j][k] + f[j + 1][k]);
            }
        }
        for (int j = i + 1; j <= n; j++) {
            for (int k = 0; k * 2 < j - i; k++) g[j][k] = 0;
            for (int k = 0; k * 2 < max(1, j - i - 1); k++) {
                if (a[j] != 1) g[j][k] = Mod(g[j][k] + g[j - 1][k]);
                if (a[j] != 0 && (k + 1) * 2 < j - i) g[j][k + 1] = Mod(g[j][k + 1] + g[j - 1][k]);
            }
        }
        if (i == n)
            for (int j = 0; j * 2 <= n; j++) ans = (ans + (int64_t)f[1][j] * (n - j) % mod * (n - j)) % mod;
        else
            for (int j = 0; j * 2 <= i; j++)
                for (int k = 0; k * 2 < n - i; k++)
                    ans = (ans + (int64_t)f[1][j] * g[n][k] % mod * (n - j - k) % mod * (i - j)) % mod;
    }
    cout << ans * Inv(Pow(2, cnt)) % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("herrah.in", "r", stdin), freopen("herrah.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}