/**
 * @file 13106.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int n, m, a[maxn], b[maxn], r[maxn], c[maxn];

bool check(int lim, int ox, int oy) {
    for (int i = 1, j = m; i <= n; i++) {
        while (j && a[i] + b[j] > lim) j--;
        r[i] = j;
    }
    for (int j = 1, i = n; j <= m; j++) {
        while (i && a[i] + b[j] > lim) i--;
        c[j] = i;
    }
    int64_t ans = 0, cur = 0;
    int px = 0, py = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        cur += min(r[i], j) - (m - max(r[i], j));
        while (j < m && min(c[j + 1], i) - (n - max(c[j + 1], i)) >= 0) j++, cur += min(c[j], i) - (n - max(c[j], i));
        if (cur >= ans) ans = cur, px = i, py = j;
    }
    return px >= ox || py >= oy;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    int ox = a[1], oy = b[1];
    sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
    int x = 1, y = 1;
    while (a[x] != ox) x++;
    while (b[y] != oy) y++;
    int l = 1, r = a[x] + b[y];
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(mid, x, y) ? r = mid : l = mid;
    }
    cout << r << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("chess.in", "r", stdin), freopen("chess.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}