/**
 * @file 14820.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

int64_t a[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    map<int, int64_t> S;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] >= 0) {
                S[j] += a[i][j];
                continue;
            }
            auto it = S.upper_bound(j);
            while (it != S.begin() && a[i][j] < 0) {
                it--;
                int64_t v = min(it->second, -a[i][j]);
                it->second -= v, a[i][j] += v;
            }
            ans += abs(a[i][j]);
        }
    for (auto [x, v] : S) ans += v;
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