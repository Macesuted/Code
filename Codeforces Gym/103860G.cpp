/**
 * @file 103860G.cpp
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

int sg(int l, int r, int p) {
    if (l > r) return 0;
    if (r % p == 1 && (r - 1) / p >= l) return sg(l, (r - 1) / p - 1, p);
    return r - l + 1 - ((r - 1) / p >= l ? (r - 1) / p - l + 1 : 0);
}

void solve(void) {
    int n, p;
    cin >> n >> p;
    uint32_t sgSum = 0;
    for (int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        sgSum ^= sg(l, r, p);
    }
    cout << (sgSum ? "First" : "Second") << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}