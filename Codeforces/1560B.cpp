/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

int a[1001], n = 0;

void work(void) {
    int a, b, c;
    cin >> a >> b >> c;
    int t = abs(a - b), n = 2 * t;
    if (a > n || b > n || c > n)
        cout << -1 << endl;
    else
        cout << (c + t - 1) % n + 1 << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}