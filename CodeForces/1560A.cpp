/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

int a[1001], n = 0;

void work(void) {
    int i;
    cin >> i;
    cout << a[i] << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    for (register int i = 1; n <= 1000; i++) {
        if (i % 3 == 0 || i % 10 == 3) continue;
        a[++n] = i;
    }
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}