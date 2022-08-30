/**
 * @file 4366.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-30
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

#define maxn 100005

int h[maxn], op[maxn];
int64_t f[maxn], g[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> f[i];
    for (int i = 1; i < n; i++) cin >> h[i] >> op[i];
    for (int i = n - 1; i; i--)
        if (op[i] == 0)
            f[h[i]] += g[i], g[h[i]] += max(f[i], g[i]);
        else if (op[i] == 1)
            f[h[i]] = max(f[h[i]] + max(f[i], g[i]), g[h[i]] + f[i]), g[h[i]] += g[i];
        else
            f[h[i]] = max(f[h[i]] + g[i], g[h[i]] + f[i]), g[h[i]] += g[i];
    cout << max(f[0], g[0]) << endl;
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