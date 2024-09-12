/**
 * @file 103185L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 10005

typedef pair<int, int> pii;

pii a[maxn];

int flr(int x, int y) { return x >= 0 ? x / y : (x / y - (x % y != 0)); }

void solve(void) {
    int n, X;
    cin >> n >> X;
    for (int i = 1, s, d; i <= n; i++) cin >> s >> d, a[i] = {s, s + d};
    pii ans = {INT_MAX, INT_MAX};
    for (int i = 0; i <= 480; i++) {
        int tot = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j].second < i) continue;
            int l = max(-1, flr(a[j].first - 1 - i, X)), r = (a[j].second - i) / X;
            tot += r - l;
        }
        ans = min(ans, pii{tot, i});
    }
    cout << ans.second << ' ' << ans.first << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}