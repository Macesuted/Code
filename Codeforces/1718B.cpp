/**
 * @file 1718B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-08
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

#define maxn 105

int a[maxn];
int64_t f[60], g[60];

void solve(void) {
    int n;
    cin >> n;
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    int p = lower_bound(g, g + 60, sum) - g;
    if (g[p] != sum) return cout << "NO" << endl, void();
    for (int i = p, lst = 0; ~i; i--) {
        int pos = 0;
        for (int j = 1; j <= n; j++)
            if (lst != j && a[j] > a[pos]) pos = j;
        if (pos == 0 || (a[lst = pos] -= f[i]) < 0) return cout << "NO" << endl, void();
    }
    return cout << "YES" << endl, void();
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    f[0] = f[1] = g[0] = 1, g[1] = 2;
    for (int i = 2; i < 60; i++) g[i] = g[i - 1] + (f[i] = f[i - 1] + f[i - 2]);

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}