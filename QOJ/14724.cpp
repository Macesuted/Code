/**
 * @file 14724.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pii = pair<int, int>;

void solve(void) {
    int n, q;
    cin >> n >> q;

    vector<pii> a;
    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, a.emplace_back(l, r);

    sort(a.begin(), a.end(), [&](const pii& a, const pii& b) -> bool { return a.second < b.second; });

    set<int> S;
    S.insert(n + 1);
    for (int i = 0; i < q; i++) {
        if (*S.lower_bound(a[i].first) <= a[i].second) continue;
        S.insert(a[i].second);
    }

    int ans = 1;
    while ((1 << ans) - 1 < S.size() - 1) ans++;

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