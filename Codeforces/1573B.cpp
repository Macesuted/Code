/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 200005

int a[maxn], b[maxn], pos[2][maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i], pos[0][a[i] = (a[i] + 1) / 2] = i;
    for (register int i = 1; i <= n; i++) cin >> b[i], pos[1][b[i] = b[i] / 2] = i;
    for (register int i = 2; i <= n; i++) pos[0][i] = min(pos[0][i], pos[0][i - 1]);
    for (register int i = n - 1; i; i--) pos[1][i] = min(pos[1][i], pos[1][i + 1]);
    int answer = 2 * n;
    for (register int i = 1; i <= n; i++) answer = min(answer, pos[0][i] + pos[1][i] - 2);
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}