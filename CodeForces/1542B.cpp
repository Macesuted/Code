/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

typedef pair<int, int> pii;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

void solve(void) {
    int n, a, b;
    cin >> n >> a >> b;
    for (register int i = 0, p = 1; i <= 31 && p <= n; i++, p *= a) {
        int t = n - p;
        if (t % b != 0) continue;
        puts("Yes");
        return;
    }
    puts("No");
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
