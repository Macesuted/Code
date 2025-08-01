/**
 * @file 1176-1002.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-01
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
    int n, m, k, p;
    cin >> n >> m >> k >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto chk = [&](int64_t lim) -> bool {
        int64_t sum = 0, rest = lim * p;
        vector<int64_t> rec;
        for (int i = 1; i <= n; i++) {
            int64_t v = min(a[i], min(rest, lim) * k);
            if (v % k) rec.push_back(v % k), v -= v % k;
            sum += v, rest -= v / k;
        }
        sort(rec.begin(), rec.end(), greater<int64_t>());
        for (auto x : rec)
            if (rest) sum += x, rest--;
        return sum >= m;
    };

    int64_t l = 0, r = 1e9;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }

    cout << r << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
