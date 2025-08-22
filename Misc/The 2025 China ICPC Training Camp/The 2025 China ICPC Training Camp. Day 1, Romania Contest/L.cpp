/**
 * @file L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int pcnt = 0;
int64_t dfs(vector<int64_t> S) {
    if (S.empty()) return 0;
    if (S.size() == 1) return S[0];

    int64_t ans = INT64_MAX;
    for (size_t t = 1; t < S.size(); t++) {
        vector<int64_t> T;
        for (size_t i = 0; i < t - 1; i++) T.push_back(S[i]);
        if (S[t - 1] != S[t]) T.push_back(abs(S[t - 1] - S[t]));
        for (size_t i = t + 1; i < S.size(); i++) T.push_back(S[i]);
        ans = min(ans, dfs(T));
    }

    return ans;
}

void solve(void) {
    int64_t n;
    cin >> n;
    int64_t l = 1, r = n, ans = 0;

    auto calc = [&](int64_t x) -> bool {
        int64_t v = x;
        v -= x / 2 % 2;
        if ((n - x) % 2 == 0)
            v -= (n - x) / 2 % 2;
        else {
            int64_t lv = x + 1, ones = (n - x) / 2, t = min(lv, ones);
            lv -= t, ones -= t, ones %= 2;
            if (lv + ones <= 1)
                v -= lv + ones;
            else {
                vector<int64_t> S;
                for (int64_t i = x + 1; i <= n; i++) S.push_back(i);
                v -= dfs(S);
            }
        }
        return v > 0;
    };

    while (l <= r && l < 3) ans += calc(l++);
    while (l <= r && r > n - 6) ans += calc(r--);
    ans += r - l + 1;

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