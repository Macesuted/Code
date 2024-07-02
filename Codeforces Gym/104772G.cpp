/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 555

int f[maxn][maxn];

void solve(void) {
    int n, p, mod;
    cin >> n >> p >> mod;
    f[0][p] = 1;
    for (int i = 1; i <= n - p; i++)
        for (int j = 0; j + i <= n - p; j++)
            for (int k = 0; k < 512; k++) f[j + i][k ^ i] = (f[j + i][k ^ i] + f[j][k]) % mod;
    cout << f[n - p][0] << endl;
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