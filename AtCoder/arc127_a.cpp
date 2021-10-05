/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 17

int pow10[maxn];

void work(void) {
    pow10[0] = 1;
    for (register int i = 1; i < maxn; i++) pow10[i] = pow10[i - 1] * 10;
    int n;
    cin >> n;
    int cnt = 0;
    for (register int i = 0; pow10[i] <= n; i++) {
        int base = 0;
        for (register int j = i; ~j; j--) {
            base += pow10[j];
            if (base > n) break;
            cnt += min(n - base + 1, pow10[j]);
        }
    }
    cout << cnt << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}