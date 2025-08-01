/**
 * @file 1176-1009.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int a[maxn], p[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;
    for (int i = 1; i <= n; i++) cin >> b[i];
    int ans = 1;
    for (int i = 2; i <= n; i++) ans += (p[b[i]] != p[b[i - 1]] + 1);
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
