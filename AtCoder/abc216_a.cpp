/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 500005
#define mod 998244353

typedef pair<int, int> pii;

void work(void) {
    int x, y;
    scanf("%lld.%lld", &x, &y);
    if (0 <= y && y <= 2)
        printf("%lld-", x);
    else if (3 <= y && y <= 6)
        printf("%lld", x);
    else
        printf("%lld+", x);
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    cout << setiosflags(ios::fixed) << setprecision(11);
    while (_--) work();
    return 0;
}