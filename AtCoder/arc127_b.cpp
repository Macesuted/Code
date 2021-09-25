/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005
#define maxl 20

int a[maxn][maxl];

void work(void) {
    int n, l;
    cin >> n >> l;
    for (register int i = 0; i < n; i++) {
        for (register int j = l - 1, S = i; j; j--) {
            int k = S % 3;
            S /= 3;
            a[i][j] = (k + 2) % 3;
            a[i + n][j] = (k + 1) % 3;
            a[i + n + n][j] = (k + 0) % 3;
        }
    }
    for (register int i = 0; i < 3 * n; i++) {
        cout << i / n;
        for (register int j = 1; j < l; j++) cout << a[i][j];
        cout << endl;
    }
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