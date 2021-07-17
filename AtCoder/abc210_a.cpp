/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios::sync_with_stdio(false);
    int n, a, x, y;
    cin >> n >> a >> x >> y;
    if (n <= a)
        cout << n * x << endl;
    else
        cout << a * x + (n - a) * y << endl;
    return 0;
}