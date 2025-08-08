/**
 * @file D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int a[maxn], b[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) cin >> b[i];

    int64_t ans = 0;
    for (int i = n, lstp = m + 1; i; i--) {
        lstp = min(lstp - 1, int(upper_bound(b + 1, b + m + 1, a[i]) - b - 1));
        ans += max(0, lstp);
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}