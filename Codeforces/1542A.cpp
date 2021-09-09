/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */
#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef pair<int, int> pii;

void solve(void) {
    int n;
    cin >> n;
    int odd = 0, even = 0;
    for (register int i = 1; i <= 2 * n; i++) {
        int t;
        cin >> t;
        if (t & 1)
            odd++;
        else
            even++;
    }
    if (odd == even)
        puts("Yes");
    else
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
