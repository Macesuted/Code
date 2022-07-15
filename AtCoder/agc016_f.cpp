/**
 * @file agc016_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-15
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

#define maxn 15
#define mod 1000000007

int con[maxn][1 << maxn];
int64_t f[1 << maxn], pow2[1000];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0, x, y; i < m; i++) cin >> x >> y, con[x - 1][1 << (y - 1)]++;
    for (int i = 0; i < n; i++)
        for (int j = 1; j < (1 << n); j++)
            if (__builtin_popcount(j) > 1)
                for (int k = 0; k < n; k++)
                    if ((j >> k & 1)) con[i][j] += con[i][1 << k];
    f[0] = 1;
    for (int S = 1; S < (1 << n); S++) {
        if ((S & 1) ^ (S >> 1 & 1)) continue;
        for (int T = S; T; T = (T - 1) & S) {
            if ((T & 1) ^ (T >> 1 & 1)) continue;
            int64_t g = 1;
            for (int i = 0; i < n; i++)
                if ((S ^ T) >> i & 1) g = g * (pow2[con[i][T]] + mod - 1) % mod;
            for (int i = 0; i < n; i++)
                if (T >> i & 1) g = g * pow2[con[i][S ^ T]] % mod;
            f[S] = (f[S] + f[S ^ T] * g) % mod;
        }
    }
    cout << (pow2[m] + mod - f[(1 << n) - 1]) % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < 1000; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}