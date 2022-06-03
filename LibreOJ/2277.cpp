/**
 * @file 2277.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-03
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

#define maxn 65
#define maxo 10005
#define mod 998244353
#define popcnt __builtin_popcountll

typedef tuple<int64_t, int64_t, int64_t> tlll;

int64_t f[maxn][maxn][maxn], g[maxo], binom[maxn][maxn];
tlll a[maxo];

void solve(void) {
    int64_t n, m, r;
    int o;
    cin >> n >> m >> r >> o;
    for (int i = 1; i <= o; i++) cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);
    a[++o] = {n, m, r};
    sort(a + 1, a + o + 1);
    f[0][0][0] = 1;
    for (int i = 0; i < maxn; i++)
        for (int j = 0; j < maxn; j++)
            for (int k = 0; k < maxn; k++) {
                for (int x = 1; x <= i; x++) f[i][j][k] = (f[i][j][k] + f[i - x][j][k] * binom[i][x]) % mod;
                for (int x = 1; x <= j; x++) f[i][j][k] = (f[i][j][k] + f[i][j - x][k] * binom[j][x]) % mod;
                for (int x = 1; x <= k; x++) f[i][j][k] = (f[i][j][k] + f[i][j][k - x] * binom[k][x]) % mod;
            }
    for (int i = 1; i <= o; i++) {
        int64_t x, y, z;
        tie(x, y, z) = a[i];
        g[i] = f[popcnt(x)][popcnt(y)][popcnt(z)];
        for (int j = 1; j < i; j++) {
            int64_t x_, y_, z_;
            tie(x_, y_, z_) = a[j];
            if ((x_ & x) == x_ && (y_ & y) == y_ && (z_ & z) == z_)
                g[i] = (g[i] + mod - g[j] * f[popcnt(x ^ x_)][popcnt(y ^ y_)][popcnt(z ^ z_)] % mod) % mod;
        }
    }
    cout << g[o] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
