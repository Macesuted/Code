/**
 * @file 9142.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t sum = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i < n; i++) sum += a[i];
    cout << sum << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}