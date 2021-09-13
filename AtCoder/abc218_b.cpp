/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef pair<int, int> pii;

void work(void) {
    for (register int i = 1; i <= 26; i++) {
        int t;
        cin >> t;
        cout << (char)('a' + t - 1);
    }
    cout << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cout << setprecision(11);
    // cin >> _;
    while (_--) work();
    return 0;
}