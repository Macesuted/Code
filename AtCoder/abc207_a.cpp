/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void work(void) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << max(max(a + b, a + c), b + c) << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}