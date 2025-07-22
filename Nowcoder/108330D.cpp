/**
 * @file 108330D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int f[maxn];

void solve(void) {
    int n, a;
    cin >> n >> a;
    string s;
    cin >> s, s = ' ' + s;
    f[0] = 0;
    for (int i = 1; i <= n; i++) f[i] = (f[i - 1] + (s[i] == '1'));
    for (int i = 1; i <= n; i++) {
        if (i + a - 1 <= n && f[i + a - 1] - f[i - 1] == a) return cout << n << endl, void();
        if (i + a <= n && f[i + a] - f[i - 1] == 0) return cout << n << endl, void();
    }
    cout << f[n] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
