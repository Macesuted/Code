/**
 * @file 108298L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int64_t a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;

    int lim = n / 2, aft = n;
    int64_t pos = 0;

    map<int64_t, int> rec;
    for (int i = 1; i <= n; i++) cin >> a[i], rec[a[i]]++;

    while (q--) {
        int p, v;
        cin >> p >> v;
        if (a[p] <= pos && a[p] + v > pos) aft++;
        rec[a[p]]--;
        a[p] += v;
        rec[a[p]]++;
        while (aft - rec.upper_bound(pos)->second >= lim) pos = rec.upper_bound(pos)->first, aft -= rec[pos];
        cout << n - aft << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
