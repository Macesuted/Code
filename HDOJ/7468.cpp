/**
 * @file 7468.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int a[maxn];

void solve(void) {
    int n, l, d;
    cin >> n >> l >> d;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 2, a + n + 1);
    if (a[1] >= l) {
        if (a[4] < l) {
            int p = 4;
            while (p < n && a[p + 1] < l) p++;
            if (a[1] - a[2] > d) return cout << "Yes" << endl, void();
        }
    } else {
        if (a[3] < l) {
            if (max(a[1], a[n]) - min(a[1], a[2]) > d) return cout << "Yes" << endl, void();
        }
    }
    cout << "No" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}