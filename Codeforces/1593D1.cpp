/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1005

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int a[maxn];

void work(void) {
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 2; i <= n; i++) ans = gcd(ans, a[i] - a[i - 1]);
    cout << (ans == 0 ? -1 : ans) << endl;
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