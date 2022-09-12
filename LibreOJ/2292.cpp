/**
 * @file 2292.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

#define maxn 55

int a[maxn], v[maxn], f[maxn][maxn][maxn][maxn], g[maxn][maxn];

void solve(void) {
    int n, A, B;
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) cin >> a[i], v[i] = a[i];
    sort(v + 1, v + n + 1);
    int vn = unique(v + 1, v + n + 1) - v - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v + 1, v + vn + 1, a[i]) - v;
    memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++) g[i][i] = A;
    for (int len = 2; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++)
            for (int vl = 1; vl <= vn; vl++)
                for (int vr = vl; vr <= vn; vr++) {
                    int tl = l, tr = r;
                    while (tl <= r && vl <= a[tl] && a[tl] <= vr) tl++;
                    while (tr >= l && vl <= a[tr] && a[tr] <= vr) tr--;
                    if (tl == r + 1)
                        f[l][r][vl][vr] = 0;
                    else {
                        f[l][r][vl][vr] = g[tl][tr];
                        for (int k = l; k < r; k++)
                            f[l][r][vl][vr] = min(f[l][r][vl][vr], f[l][k][vl][vr] + f[k + 1][r][vl][vr]);
                    }
                    g[l][r] = min(g[l][r], f[l][r][vl][vr] + A + B * (v[vr] - v[vl]) * (v[vr] - v[vl]));
                }
    cout << g[1][n] << endl;
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