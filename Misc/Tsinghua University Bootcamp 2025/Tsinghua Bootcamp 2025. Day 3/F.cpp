/**
 * @file F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

using pii = pair<int, int>;

pii a[maxn];
int cost[maxn][3];
int64_t f[maxn][3];

void solve(void) {
    int l, n;
    cin >> l >> n;

    int L = 1e9, R = 1;
    for (int i = 1, l, r; i <= n; i++) cin >> l >> r, a[i] = {l, r}, L = min({L, l, r}), R = max({R, l, r});

    auto solve = [&](void) -> int64_t {
        int64_t tot = R - L;
        vector<pii> rec;
        for (int i = 1; i <= n; i++)
            if (a[i].first > a[i].second) rec.emplace_back(a[i].second, a[i].first);
        sort(rec.begin(), rec.end());

        vector<pii> cac;
        for (auto [l, r] : rec)
            if (cac.empty() || cac.back().second < l)
                cac.emplace_back(l, r);
            else
                cac.back().second = max(cac.back().second, r);

        if (cac.empty()) return tot;

        int m = cac.size();

        cost[0][0] = cac[0].first - L;
        for (int i = 1; i < m; i++) cost[i][0] = cac[i].first - cac[i - 1].second;

        for (int i = 0; i < m; i++) tot += cost[i][1] = cac[i].second - cac[i].first;

        cost[m - 1][2] = R - cac[m - 1].second;
        for (int i = m - 2; ~i; i--) cost[i][2] = cac[i + 1].first - cac[i].second;

        f[0][0] = cost[0][0], f[0][1] = cost[0][1], f[0][2] = cost[0][2];
        for (int i = 1; i < m; i++) {
            int64_t mv = INT64_MAX;
            for (int t = 0; t < 3; t++) f[i][t] = cost[i][t] + (mv = min(mv, f[i - 1][t]));
        }

        return min({f[m - 1][0], f[m - 1][1], f[m - 1][2]}) + tot;
    };

    int64_t ans = solve();

    tie(L, R) = make_pair(l + 1 - R, l + 1 - L);
    for (int i = 1; i <= n; i++) a[i].first = l + 1 - a[i].first, a[i].second = l + 1 - a[i].second;

    cout << min(solve(), ans);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}