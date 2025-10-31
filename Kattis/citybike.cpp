/**
 * @file citybike.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int a[maxn];

void solve(void) {
    int n, d, c;
    cin >> n >> d >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int l = 0, r = d + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;

        auto chk = [&](int lim) -> bool {
            for (int i = 1, sum = 0; i <= n; i++) {
                sum += a[i] - lim;
                if (sum > 0) sum = 0;
                if (sum < -c) return false;
            }

            return true;
        };

        (chk(mid) ? l : r) = mid;
    }
    int L = l;

    l = -1, r = d;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;

        auto chk = [&](int lim) -> bool {
            for (int i = 1, sum = 0; i <= n; i++) {
                sum += lim - a[i];
                if (sum > 0) sum = 0;
                if (sum < -c) return false;
            }

            return true;
        };

        (chk(mid) ? r : l) = mid;
    }
    int R = r;

    cout << max(0, R - L) << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}