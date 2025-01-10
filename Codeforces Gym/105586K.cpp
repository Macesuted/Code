/**
 * @file 105586K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

#define maxn 100005
#define mod 1'000'000'007

int64_t Mod(int64_t a) { return a >= mod ? a - mod : a; }

int64_t f[3][maxn], g[4][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) f[0][i] = f[1][i] = f[2][i] = g[0][i] = g[1][i] = g[2][i] = g[3][i] = 0;
    for (int i = 1, op, x; i <= m; i++) {
        cin >> op >> x;
        if (op == 1)
            f[0][x]++;
        else
            g[0][x]++, g[0][x + 1]++;
    }
    for (int t = 1; t <= 2; t++)
        for (int i = 1; i <= n; i++) f[t][i] = Mod(f[t][i - 1] + f[t - 1][i]);
    for (int t = 1; t <= 3; t++)
        for (int i = 1; i <= n; i++) g[t][i] = Mod(g[t][i - 1] + g[t - 1][i]);
    for (int i = 1; i <= n; i++) cout << Mod(f[2][i] + g[3][i]) << ' ';
    cout << endl;
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