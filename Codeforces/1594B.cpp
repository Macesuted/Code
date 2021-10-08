/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

typedef pair<int, int> pii;

void work(void) {
    int n, k;
    cin >> n >> k;
    int ans = 0;
    for (int i = 0, pow = 1; i < 32; i++, pow = pow * n % mod)
        if (k >> i & 1) ans = (ans + pow) % mod;
    cout << ans << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}