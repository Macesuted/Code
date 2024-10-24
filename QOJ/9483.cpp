/**
 * @file 9483.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 300005

int a[maxn], f[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], f[i] = a[i];
    for (int i = n - k; i; i--) f[i] = max(f[i], f[i + k]);
    for (int i = 1; i <= n; i++) {
        while (f[i] != a[i]) i += k;
        cout << a[i] << ' ';
    }
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
