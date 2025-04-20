/**
 * @file 10325.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int pre[maxn];

void solve(void) {
    int n;
    cin >> n;
    string s;
    cin >> s, s = ' ' + s;

    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (s[i] == '1');

    int xp = 0, xr = -1, rest1 = 2;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && s[l] == s[r + 1]) r++;
        if (s[l] == '0') {
            if ((r - l + 1) * 2 > (n - pre[n])) xp = l, xr = r;
            rest1 = min(rest1, (pre[l - 1] > 0) + (pre[n] - pre[r] > 0));
        }
    }

    if (xp == 0) {
        if ((n - pre[n]) % 2 == 0) return cout << (n - pre[n]) / 2 + pre[n] - 1 << endl, void();
        return cout << (n - pre[n]) / 2 + pre[n] - rest1 << endl, void();
    }

    cout << (n - pre[n] - (xr - xp + 1)) + pre[n] - (pre[xp - 1] > 0) - (pre[n] - pre[xr] > 0) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
