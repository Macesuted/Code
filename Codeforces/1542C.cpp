/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

typedef pair<int, int> pii;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

void solve(void) {
    int n;
    cin >> n;
    int pre = 1, answer = 0;
    for (register int i = 2; i <= 43 && pre <= n; i++) {
        answer = (answer + i * ((n / pre) % mod + mod - (n / (i / gcd(i, pre) * pre)) % mod)) % mod;
        pre = pre / gcd(pre, i) * i;
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(3);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}
