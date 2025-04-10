/**
 * @file 9917.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int a[maxn];

void solve(void) {
    int n, mv = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], mv = max(mv, a[i]);
    for (int i = 1; i <= n; i++)
        if (a[i] == mv) cout << i << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
