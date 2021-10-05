/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void work(void) {
    int n;
    cin >> n;
    int c = 0;
    while ((c + 1) * (c + 1) < n) c++;
    n -= c * c;
    if (n <= c + 1)
        cout << n << ' ' << c + 1 << endl;
    else
        cout << c + 1 << ' ' << 2 * c + 1 - n + 1 << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}