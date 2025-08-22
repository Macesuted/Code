/**
 * @file arc204_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-17
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

#define maxn 5005
#define mod 998244353

int64_t a[maxn], b[maxn];
int f[maxn][maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n, L, R;
    cin >> n >> L >> R;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = a[i - 1] - a[i];
    for (int i = 1; i <= n; i++) cin >> b[i], b[i] = b[i - 1] + b[i];

    auto calc = [&](int64_t lim) {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++) f[i][j] = 0;

        f[0][0] = 1;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= i; j++) {
                if (i < n && a[i + 1] + b[j] + lim >= 0) f[i + 1][j] = Mod(f[i + 1][j] + f[i][j]);
                if (j < i) f[i][j + 1] = Mod(f[i][j + 1] + f[i][j]);
            }
        return f[n][n];
    };

    cout << Mod(calc(R - (a[n] + b[n])) + mod - calc(L - 1 - (a[n] + b[n]))) << endl;

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