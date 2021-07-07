/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(void) {
    int n;
    cin >> n;
    int sum = 0;
    for (register int i = 1, t; i <= n; i++) {
        cin >> t;
        sum += t;
    }
    sum %= n;
    cout << sum * (n - sum) << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}