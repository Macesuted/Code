/**
 * @file 1498C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005
#define mod 1'000'000'007

int64_t f[maxn][maxn];

int64_t Mod(int64_t a) { return a >= mod ? a - mod : a; }

void solve(void) {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) f[k][i] = 1;

    int64_t ans = 1;
    for (int i = k - 1; i >= 1; i--) {
        if ((k - i) & 1) {
            f[i][n] = f[i + 1][n];
            for (int j = n - 1; j >= 1; j--) f[i][j] = Mod(f[i + 1][j] + f[i][j + 1]);
            ans = Mod(ans + f[i][1]);
        } else {
            f[i][1] = 0;
            for (int j = 2; j <= n; j++) f[i][j] = Mod(f[i + 1][j] + f[i][j - 1]);
            ans = Mod(ans + f[i][n]);
        }
    }

    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}