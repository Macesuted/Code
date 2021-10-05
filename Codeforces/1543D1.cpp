/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

int ask(int x) {
    cout << x << endl;
    int t;
    cin >> t;
    return t;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (register int i = 0, pre = 0; i < n; i++) {
        int a = i ^ pre;
        int ret = ask(a);
        if (ret == 1) return;
        pre ^= a;
    }
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