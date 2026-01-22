/**
 * @file 15490.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005
#define mod 1'000'000'007

int Mod(int x) { return x >= mod ? x - mod : x; }

int f[64][maxn][maxn];

void solve(void) {
    int64_t n;
    int p;
    cin >> n >> p;

    f[62][0][0] = 1;
    for (int b = 61; b >= 0; b--)
        for (int i = 0; i <= p; i++)
            for (int j = 0, sum = 0; j <= p; j++) {
                sum = Mod(sum + f[b + 1][i][j]);
                int v = i * 2 + (n >> b & 1) - j;
                if (0 <= v && v <= p) f[b][v][j] = sum;
            }

    for (int i = 1; i <= p; i++) cout << f[0][0][i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
