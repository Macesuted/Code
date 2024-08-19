/**
 * @file 7551.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

int a[maxn], b[maxn];

void solve(void) {
    int n, m, k;
    int64_t sum = 0;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i] - 1;
    for (int i = 1; i <= n; i++) cin >> b[i];
    cout << (min(sum, (int64_t)m - 1) < k ? "YES" : "NO") << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}