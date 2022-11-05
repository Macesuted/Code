/**
 * @file agc045_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
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

#define maxn 5005
#define mod 1000000007

int64_t f[2][maxn], g[maxn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }
int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n, a, b;
    cin >> n >> a >> b;
    if (a > b) swap(a, b);
    g[0] = 1;
    for (int i = 1; i <= b; i++) {
        g[i] = g[i - 1];
        for (int j = a; j <= i - 2; j++) g[i] = Mod(g[i] + g[i - j - 1]);
    }
    int64_t ans = 0;
    for (int i = 1; i < a; i++) f[1][1 + i] = 1;
    for (int i = 1; i < b; i++) f[0][1 + i] = g[i + 1];
    for (int i = 2; i < n; i++) {
        for (int j = 1; j < a && i + j <= n; j++) f[1][i + j] = Mod(f[1][i + j] + f[0][i]);
        for (int j = 1; j < b && i + j <= n; j++) f[0][i + j] = (f[0][i + j] + f[1][i] * g[j]) % mod;
    }
    for (int i = 1; i < a; i++) ans = Mod(ans + f[0][n - i + 1]);
    for (int i = 1; i < b; i++) ans = (ans + f[1][n - i + 1] * g[i + 1]) % mod;
    cout << Mod(Pow(2, n) + mod - ans) << endl;
    return;
}

bool mem2;

int main() {
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