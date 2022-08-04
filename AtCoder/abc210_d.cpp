/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[1005][1005], f[1005][1005];

signed main() {
    ios::sync_with_stdio(false);
    int n, m, c;
    cin >> n >> m >> c;
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++) cin >> a[i][j];
    int answer = 0x3f3f3f3f3f3f3f3f;
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= m; j++) {
            f[i][j] = 0x3f3f3f3f3f3f3f3f;
            if (i > 1) f[i][j] = min(f[i][j], f[i - 1][j] + c);
            if (j > 1) f[i][j] = min(f[i][j], f[i][j - 1] + c);
            answer = min(answer, f[i][j] + a[i][j]);
            f[i][j] = min(f[i][j], a[i][j]);
        }
        for (register int j = m - 1; j; j--) f[i][j] = min(f[i][j], f[i][j + 1] + c);
    }
    cout << answer << endl;
    return 0;
}