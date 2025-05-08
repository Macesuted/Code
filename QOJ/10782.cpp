/**
 * @file 10782.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1'000'000'033

#define maxn 105

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int64_t a[maxn][maxn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n;
    string s;
    cin >> n >> s;

    int64_t tar = 0;
    for (char c : s) tar = (tar * 10 + c - '0') % mod;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j], a[i][j] = Mod(a[i][j] + mod);

    int64_t ans = 1;
    for (int i = 1; i <= n; i++) {
        int p = i;
        while (!a[p][i]) p++;
        if (p != i) {
            ans = Mod(mod - ans);
            for (int j = i; j <= n; j++) swap(a[p][j], a[i][j]);
        }

        ans = ans * a[i][i] % mod;
        int64_t v = inv(a[i][i]);
        for (int j = i; j <= n; j++) a[i][j] = a[i][j] * v % mod;

        for (int j = 1; j <= n; j++) {
            if (i == j || !a[j][i]) continue;
            for (int k = n; k >= i; k--) a[j][k] = Mod(a[j][k] + mod - a[i][k] * a[j][i] % mod);
        }
    }

    cout << "-+"[ans == tar] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
