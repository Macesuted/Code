/**
 * @file A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-06
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

#define maxn 105

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int x = 1; x <= n; x++)
        for (int y = x + 1; y <= n; y++) {
            if (a[x] <= a[y]) continue;
            cout << "YES" << endl;
            cout << 2 << endl;
            cout << a[x] << ' ' << a[y] << endl;
            return;
        }
    cout << "NO" << endl;
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