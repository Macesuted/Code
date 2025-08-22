/**
 * @file F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pll = pair<int64_t, int64_t>;

void solve(void) {
    int64_t n, x;
    cin >> n >> x;

    vector<pll> ans;
    int64_t l = 1, r = n;
    while (true) {
        int64_t mid = (l + r) / 2;
        if (mid == x) break;
        if (x < mid)
            ans.emplace_back(mid + 1, r), r = mid - 1;
        else
            ans.emplace_back(l, mid - 1), l = mid + 1;
    }

    int d = ans.size();
    int64_t cnt = d + 1;

    for (int i = 0; i < d; i++) {
        auto [l, r] = ans[i];
        if (r < x)
            cnt += min(r - l + 1, ((int64_t)1 << (d - i)) - 1);
        else if (d - i - 1 >= 0)
            cnt += min(r - l + 1, ((int64_t)1 << (d - i - 1)) - 1);
    }

    cout << cnt << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}