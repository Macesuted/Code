/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005
#define mod 1000000007

typedef pair<int, int> pii;

int f[maxn];

void work(void) {
    int n;
    cin >> n;
    n--;
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = 16 * f[i - 1] % mod * f[i - 1] % mod;
    cout << f[n] * 6 % mod << endl;
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