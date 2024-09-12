/**
 * @file 1906M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    int64_t ans = sum / 3;
    for (int i = 1; i <= n; i++) ans = min(ans, sum - a[i]);
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}