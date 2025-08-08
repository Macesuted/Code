/**
 * @file E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-08
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

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first;
    for (int i = 1; i <= n; i++) cin >> a[i].second;

    sort(a + 1, a + n + 1);
    for (int i = n - 1; i; i--) a[i].second = min(a[i].second, a[i + 1].second);

    auto chk = [&](int x) -> bool {
        int v = a[x].first;

        for (int i = 1; i <= n; i++) {
            if (i == x) continue;
            if (a[i].first >= v) return false;
            v++;
        }

        return true;
    };

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }

    if (r == n + 1) return cout << -1 << endl, void();

    return cout << a[r].second << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}