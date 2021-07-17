/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef pair<int, int> pii;

pii a[100005];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

signed main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (register int i = 1; i <= m; i++) cin >> a[i].second >> a[i].first;
    sort(a + 1, a + m + 1);
    int answer = 0;
    for (register int i = 1; n > 1 && i <= m; i++) {
        int tn = gcd(n, a[i].second);
        answer += (n - tn) * a[i].first;
        n = tn;
    }
    if (n > 1)
        cout << -1 << endl;
    else
        cout << answer << endl;
    return 0;
}