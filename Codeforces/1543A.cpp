/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(void) {
    int x, y;
    cin >> x >> y;
    if (x < y) swap(x, y);
    int a = x - y;
    if (a == 0) cout << 0 << ' ' << 0 << endl;
    else cout << a << ' ' << min(x % a, a - x % a) << endl;
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