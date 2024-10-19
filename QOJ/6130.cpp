/**
 * @file 6130.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int64_t a[maxn], c[maxn];
int n;
int64_t m;

bool check(int64_t lim) {
    for (int i = 1; i <= n; i++) c[i] = (lim - 1) / a[i] + 1;
    int64_t rest = m;
    for (int i = 1; i < n && rest >= 0; i++) {
        c[i]--, rest--;
        if (c[i] > 0) c[i + 1] -= c[i], rest -= 2 * c[i], c[i] = 0;
    }
    if (c[n] > 0) rest -= 2 * c[n] - 1;
    return rest >= 0;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t l = 0, r = 1e18;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1;
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