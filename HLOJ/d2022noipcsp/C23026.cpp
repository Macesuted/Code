/**
 * @file C23026.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int a[15];
double f[1 << 15], g[1 << 15], C[16][16], v[15][15];

void solve(void) {
    int n, m, k, U;
    cin >> n >> m >> k, U = (1 << n) - 1;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    for (int i = k + 1; i <= n; i++) {
        int s = min(i, m);
        for (int j = 0; j <= i - s; j++) v[i][j] = C[i - j - 1][s - 1] / C[i][s];
    }
    for (int S = 1; S <= U; S++) {
        if (__builtin_popcount(S) <= k) continue;
        int t = __builtin_popcount(S), s = min(m, t);
        vector<int> b;
        for (int i = 0; i < n; i++)
            if (S >> i & 1) b.push_back(i);
        double p1 = 0, q1 = 1;
        for (int i = t - 1; i >= s - 1; i--) {
            p1 += v[t][t - 1 - i] * (a[b[i]] + g[S ^ (1 << b[i])]), q1 -= v[t][t - 1 - i];
            double p2 = 0, q2 = 1, mn = 1e18;
            for (int j = 0; j <= t - s; j++) {
                p2 += v[t][j] * (a[b[j]] + f[S ^ (1 << b[j])]), q2 -= v[t][j];
                mn = min(mn, (p1 + q1 * p2) / (1 - q1 * q2));
            }
            f[S] = max(f[S], mn);
        }
        for (int i = 0; i <= t - s; i++) g[S] += v[t][i] * min(a[b[i]] + f[S ^ (1 << b[i])], f[S]);
    }
    cout << fixed << setprecision(8) << f[U] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("card.in", "r", stdin), freopen("card.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < 16; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}