/**
 * @file 6128.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for (int i = 1; i <= n; i++) a[i] = (s[i - 1] ^ t[i - 1]);
    a[n + 1] = 0;
    for (int i = n + 1; i; i--) a[i] ^= a[i - 1];
    int cnt = 0;
    for (int i = 1; i <= n + 1; i++) cnt += a[i];
    if (cnt == 0)
        cout << (int64_t)n * (n + 1) / 2 << endl;
    else if (cnt == 2)
        cout << 2 * (n - 1) << endl;
    else if (cnt == 4)
        cout << 6 << endl;
    else
        cout << 0 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}