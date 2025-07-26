/**
 * @file 1174-1004.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int a[15], A[15], B[15], id[15];

void solve(void) {
    int n = 13;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto check = [&](int lim) -> bool {
        int sumA = 0, sumB = 0;
        for (int i = 1; i <= n; i++) {
            A[i] = min({a[i] / 3, lim}), sumA += A[i];
            B[i] = min({a[i] - 3 * A[i], lim - A[i]}), sumB += B[i];
        }
        if (sumA < lim) return false;

        for (int i = 1; i <= n; i++) id[i] = i;

        sort(id + 1, id + n + 1, [&](int x, int y) { return (lim - A[x] - B[x]) / 2 > (lim - A[y] - B[y]) / 2; });
        for (int p = 1; p <= n; p++) {
            int i = id[p], x = min({sumA - lim, (lim - A[i] - B[i]) / 2, A[i]});
            A[i] -= x, sumA -= x;
            B[i] += 3 * x, sumB += 3 * x;
        }

        sort(id + 1, id + n + 1, [&](int x, int y) { return lim - A[x] - B[x] > lim - A[y] - B[y]; });
        for (int p = 1; p <= n; p++) {
            int i = id[p], x = min({sumA - lim, lim - A[i] - B[i], A[i]});
            A[i] -= x, sumA -= x;
            B[i] += 2 * x, sumB += 2 * x;
        }

        for (int i = 1; i <= n; i++) {
            int x = min(sumA - lim, A[i]);
            A[i] -= x, sumA -= x;
            B[i] += x, sumB += x;
        }

        return sumB >= lim;
    };

    int l = 0, r = 1e7;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) ? l : r) = mid;
    }

    cout << l << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
