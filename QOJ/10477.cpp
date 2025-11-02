/**
 * @file 10477.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005
#define mod 998244353

using pii = pair<int, int>;

void solve(void) {
    auto get = [&](void) -> vector<pair<pii, pii>> {
        string s;
        cin >> s;

        int n = (s.size() + 2) / 3, cnt = 0;

        vector<pair<pii, pii>> ans(n + 1);
        stack<pii> S;
        for (auto c : s) {
            if (c == '(') continue;
            if (c == '1') {
                cnt++;
                S.emplace(cnt, cnt);
            } else {
                auto y = S.top();
                S.pop();
                auto x = S.top();
                S.pop();
                ans[y.first] = {x, y};
                S.emplace(x.first, y.second);
            }
        }

        return ans;
    };

    vector<pair<pii, pii>> S = get(), T = get();

    int64_t ans = 1;
    for (size_t i = 1; i < S.size(); i++) {
        auto xS = S[i].first, xT = T[i].first, yS = S[i].second, yT = T[i].second;
        ans = ans * (min(xS.second, xT.second) - max(xS.first, xT.first) + 1) % mod;
        ans = ans * (min(yS.second, yT.second) - max(yS.first, yT.first) + 1) % mod;
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
