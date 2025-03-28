/**
 * @file 103860F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int64_t a[21];
int64_t f[1 << 21];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, greater<int64_t>());
    int64_t v;
    cin >> v;

    int64_t ans = 0;
    for (int S = 0; S < (1 << (n - 1)); S++) {
        int64_t cur = v;
        for (int x = 0; x < n - 1; x++)
            if (S >> x & 1) cur %= a[x];
        ans = max(ans, cur % a[n - 1]);
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}