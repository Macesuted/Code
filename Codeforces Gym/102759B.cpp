/**
 * @file 102759B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-08
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

int n, m, a[maxn], b[maxn], p[maxn], lef[maxn], rig[maxn], sum[maxn];
bool banl[maxn], banr[maxn];

void solve(void) {
    int n, m, maxB = -1e9, minB = 1e9;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[p[i] = i];
    for (int i = 1; i <= m; i++) cin >> b[i], maxB = max(maxB, b[i]), minB = min(minB, b[i]);
    sort(p + 1, p + n + 1, [&](int x, int y) { return a[x] < a[y]; });
    for (int i = n, l = 1, r = m, vl = 1e9, vr = 1e9; i; i--) {
        while (l <= m && a[p[i]] + b[l] < 0) vl = min(vl, b[l++]);
        while (r >= 1 && a[p[i]] + b[r] < 0) vr = min(vr, b[r--]);
        lef[p[i]] = vl, rig[p[i]] = vr;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = p[i]; j >= 1 && !banl[j] && a[j] + lef[p[i]] < 0; j--) banl[j] = true;
        for (int j = p[i]; j <= n && !banr[j] && a[j] + rig[p[i]] < 0; j++) banr[j] = true;
    }
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (!banr[i]);
    int64_t ans = 0;
    for (int i = n, u = n + 1, d = n; i; i--) {
        if (a[i] + minB >= 0) u = i;
        if (a[i] + maxB < 0) d = i - 1;
        if (!banl[i] && u <= d) ans += sum[d] - sum[u - 1];
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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