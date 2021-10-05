/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 505
#define mod 998244353

string a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (register int i = 1; i <= n; i++) cin >> a[i], a[i] = ' ' + a[i];
    long long answer = 1;
    for (register int t = 2; t <= n + m; t++) {
        bool visB = false, visR = false, visW = false;
        for (register int i = 1; i < t; i++) {
            register int j = t - i;
            if (!(1 <= i && i <= n && 1 <= j && j <= m)) continue;
            if (a[i][j] == 'B') visB = true;
            if (a[i][j] == 'R') visR = true;
            if (a[i][j] == '.') visW = true;
        }
        if (visB && visR) {
            cout << 0 << endl;
            return 0;
        }
        if (!visB && !visR) answer = answer * 2 % mod;
    }
    cout << answer << endl;
    return 0;
}
