/**
 * @file 11379.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-13
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
#define maxv 1000005

int a[maxn], f[maxv], g[maxv];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    f[0] = 0;
    for (int i = 1; i < n; i++)
        for (int x = a[i]; x < a[i + 1]; x++) f[x] = f[x - a[i]] + 1;
    for (int i = 0; i < a[n]; i++) g[f[i]]++;
    for (int i = 1; i < a[n]; i++) g[i] += g[i - 1];

    while (q--) {
        int m;
        cin >> m;
        cout << g[min(m, a[n] - 1)] << ' ';
    }
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}