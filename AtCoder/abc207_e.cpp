/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 3005
#define mod 1000000007

int a[maxn], f[maxn][maxn], cnt[maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int j = n; j; j--) {
        memset(cnt, 0, sizeof(cnt));
        cnt[0] = 1;
        for (register int i = n, tat = 0; i; i--) {
            tat = (tat + a[i]) % j;
            f[i][j] = cnt[tat];
            cnt[tat] = (cnt[tat] + f[i][j + 1]) % mod;
        }
    }
    cout << f[1][1] << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}