/**
 * @file 4837.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t pre = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) a[i] += a[i - 1];
    for (int i = 1; i < n; i++)
        if (a[i] <= 0) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}