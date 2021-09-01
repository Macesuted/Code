/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void work(void) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int t = c * d - b;
    if (t <= 0) {
        cout << -1 << endl;
        return;
    }
    int ans = a / t;
    if (a % t) ans++;
    cout << ans << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}