/**
 * @file 1625C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 505

int d[maxn], a[maxn], f[maxn][maxn];

void solve(void) {
    int n, l, k;
    cin >> n >> l >> k, d[n + 1] = l;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            if (f[i][j] == 0x3f3f3f3f) continue;
            for (int x = i + 1; x <= n + 1 && j + (x - i - 1) <= k; x++)
                f[x][j + (x - i - 1)] = min(f[x][j + (x - i - 1)], f[i][j] + (d[x] - d[i]) * a[i]);
        }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++) ans = min(ans, f[n + 1][i]);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
