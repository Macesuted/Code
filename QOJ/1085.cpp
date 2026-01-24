/**
 * @file 1085.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define maxlgn 25
#define mod 998244353

int64_t f[maxn], g[maxlgn];
int lg2[maxn];

void solve(void) {
    int n;
    cin >> n;

    f[1] = g[0] = 1;
    int64_t sum = 2;
    for (int i = 2; i <= n; i++) {
        f[i] = sum;
        for (int j = 0; j < lg2[i]; j++)
            if (i >> j & 1) f[i] = (f[i] + mod - g[j]) % mod;
        g[lg2[i]] = (g[lg2[i]] + f[i]) % mod, sum = (sum + f[i]) % mod;
    }

    cout << (sum + mod - 1) % mod << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int i = 2; i < maxn; i++) lg2[i] = lg2[i >> 1] + 1;

    int _ = 1;
    while (_--) solve();

    return 0;
}
