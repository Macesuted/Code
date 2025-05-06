/**
 * @file 108218G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pii = pair<int, int>;

void solve(void) {
    int n;
    int64_t A, B;
    cin >> n >> A >> B;

    vector<pii> a;
    for (int i = 1, x, y; i <= n; i++) cin >> x >> y, a.emplace_back(x, y);

    int64_t ans = 0;

    auto solve = [&](void) {
        vector<int64_t> rec[5];
        for (auto [x, y] : a) {
            if (y == 0) rec[0].push_back(x);
            if (x == A) rec[1].push_back(y), rec[4].push_back(y);
            if (y == B) rec[2].push_back(x);
            if (x == 0) rec[3].push_back(y), rec[4].push_back(y);
        }
        for (int t = 0; t < 5; t++) sort(rec[t].begin(), rec[t].end());

        int64_t maxLen = 0;
        for (int i = 1; i < (int)rec[0].size(); i++) maxLen = max(maxLen, rec[0][i] - rec[0][i - 1]);

        int u = 0, v = 0;

        for (int yi = 0; yi < (int)rec[4].size(); yi++) {
            int64_t y = rec[4][yi];
            if (yi)
                ans = max(ans, (rec[4][yi] - rec[4][yi - 1]) * A);
            else if (rec[0].empty())
                ans = max(ans, rec[4][yi] * A);

            if (rec[0].empty()) continue;

            while (u + 1 < (int)rec[1].size() && rec[1][u + 1] < y) u++;
            while (v + 1 < (int)rec[3].size() && rec[3][v + 1] < y) v++;
            if (rec[1].empty() || rec[1][u] >= y)
                ans = max(ans, (A - rec[0].back()) * y);
            else
                ans = max(ans, (A - rec[0].front()) * (y - rec[1][u]));
            if (rec[3].empty() || rec[3][v] >= y)
                ans = max(ans, rec[0].front() * y);
            else
                ans = max(ans, rec[0].back() * (y - rec[3][v]));

            ans = max(ans, maxLen * y);
        }

        return;
    };

    auto rotate = [&](void) {
        for (int i = 0; i < n; i++) a[i] = {B - a[i].second, a[i].first};
        swap(A, B);
        return;
    };

    for (int t = 0; t < 4; t++) solve(), rotate();

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