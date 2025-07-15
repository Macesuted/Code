/**
 * @file 108298I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 450

using pll = pair<int64_t, int64_t>;

vector<pll> f[maxn][maxn];
int a[maxn];
int64_t sum[maxn];

int64_t getSum(int l, int r) { return sum[r] - sum[l - 1]; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) f[i][j].clear();
    for (int i = 1; i <= n; i++) f[i][i].emplace_back(0, 0);

    auto getCost = [&](int l, int r, int x) -> int64_t {
        return min(getSum(l, x), getSum(x + 1, r)) * int64_t(ceil(log2(getSum(l, r))));
    };
    auto query = [&](int l, int r, int64_t lim) -> int64_t {
        auto p = lower_bound(f[l][r].begin(), f[l][r].end(), pll{lim, INT64_MAX});
        if (p == f[l][r].begin()) return -1;
        return prev(p)->second;
    };

    for (int len = 2; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++) {
            for (int x = l; x < r; x++) {
                int64_t lim = abs(getSum(l, x) - getSum(x + 1, r)), sum = getCost(l, r, x);
                int64_t v = query(l, x, lim);
                if (v == -1) continue;
                sum += v;
                v = query(x + 1, r, lim);
                if (v == -1) continue;
                sum += v;
                f[l][r].emplace_back(lim, sum);
            }
            sort(f[l][r].begin(), f[l][r].end());
            for (size_t i = 1; i < f[l][r].size(); i++) f[l][r][i].second = min(f[l][r][i].second, f[l][r][i - 1].second);
        }

    for (int i = 1; i < n; i++) {
        int64_t lim = abs(getSum(1, i) - getSum(i + 1, n)), ans = getCost(1, n, i);
        int64_t v = query(1, i, lim);
        if (v == -1) {
            cout << -1 << ' ';
            continue;
        }
        ans += v;
        v = query(i + 1, n, lim);
        if (v == -1) {
            cout << -1 << ' ';
            continue;
        }
        ans += v;
        cout << ans << ' ';
    }
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
