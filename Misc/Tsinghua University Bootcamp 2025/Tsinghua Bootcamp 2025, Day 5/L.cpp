/**
 * @file L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 400005

int a[maxn], b[maxn];
int64_t f[maxn];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i], b[i] = (b[i] ? ~0 : 0);

    memset(f, 0xc0, sizeof f);

    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int v = a[i], j = min(i - 1., max(10000., 0.135 * (i - 1))), ed = max(0., min(i - 10000., 0.09 * (i - 1)));
             j >= ed; j--)
            f[j + 1] = max(f[j + 1], f[j]), f[j] += b[i - j] & v;

    int pos = 0;
    for (int i = 0; i <= n; i++)
        if (f[i] > f[pos]) pos = i;

    cout << f[pos] << endl;

    return 0;
}
