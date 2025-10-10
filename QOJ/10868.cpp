/**
 * @file 10868.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int f[maxn];

void solve(void) {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] + (s[i - 1] == 'H');

    for (int i = 1; i <= n; i++) {
        int p = 0, ans = 0;
        while (i + f[p] <= n && p < i + f[p]) p = i + f[p], ans++;
        cout << ans << ' ';
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