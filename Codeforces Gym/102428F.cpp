/**
 * @file 102428F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 5005
#define mod 1000000007

int64_t f[maxn][maxn], g1[maxn][maxn], g2[maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, m;
    cin >> n >> m, m -= n;

    f[m][n] = 1;
    for (int i = 1; i <= n; i++) g1[m][i] = 1, g2[m][i] = n;

    for (int i = m - 1; ~i; i--) {
        for (int j = 1; j <= n && i + j <= m; j++) {
            f[i][j] = (g2[i + j][j] + (mod - j + 1) * g1[i + j][j]) % mod;
        }
        for (int j = m; j; j--) g1[i][j] = (g1[i][j + 1] + f[i][j]) % mod, g2[i][j] = (g2[i][j + 1] + f[i][j] * j) % mod;
    }

    cout << g1[0][1] << endl;

    return 0;
}