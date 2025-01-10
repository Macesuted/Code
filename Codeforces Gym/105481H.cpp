/**
 * @file 105481H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxbit 22

int bt[maxbit];
int64_t f[maxbit][maxbit * 10], g[2][maxbit][maxbit * 10], sl[maxbit], sr[maxbit];

int64_t solve(int64_t n) {
    int mxb = 0;
    {
        int64_t v = 1;
        while (n >= v) bt[++mxb] = n / v % 10, v *= 10;
    }

    for (int i = 0; i <= mxb + 1; i++)
        for (int j = 0; j <= mxb * 9; j++) f[i][j] = g[0][i][j] = g[1][i][j] = 0;

    sl[mxb + 1] = 0;
    for (int i = mxb; i >= 1; i--) sl[i] = sl[i + 1] + bt[i];
    sr[0] = 0;
    for (int i = 1; i <= mxb; i++) sr[i] = sr[i - 1] + bt[i];

    for (int i = mxb; i; i--) {
        for (int t = 0; t < bt[i]; t++) f[i][sl[i + 1] + t]++;
        for (int j = 0; j <= (mxb - i) * 9; j++)
            for (int t = 0; t < 10; t++) f[i][j + t] += f[i + 1][j];
    }

    g[0][0][0] = g[1][0][0] = 1;
    for (int i = 1; i <= mxb; i++) {
        for (int t = 0; t < bt[i]; t++)
            for (int j = t; j <= i * 9; j++) g[1][i][j] += g[0][i - 1][j - t];
        for (int j = bt[i]; j <= i * 9; j++) g[1][i][j] += g[1][i - 1][j - bt[i]];

        for (int t = 0; t < 10; t++)
            for (int j = t; j <= i * 9; j++) g[0][i][j] += g[0][i - 1][j - t];
    }

    int64_t ans = 0;
    for (int x = 1; x <= bt[mxb]; x++) ans += x;

    for (int i = mxb; i > 1; i--) {
        for (int x = 1; x <= 9; x++) {
            for (int d1 = 0; d1 <= (mxb - i + 1) * 9; d1++)
                for (int d2 = max(x, d1 + 1); d2 <= min(d1 + x, (i - 1) * 9); d2++) {
                    if (d1 == sl[i] && x == bt[i - 1]) ans += (d2 - d1) * (i > 2 ? g[1][i - 2][d2 - x] : (d2 == x));
                    if (d1 == sl[i] && x < bt[i - 1]) ans += (d2 - d1) * (i > 2 ? g[0][i - 2][d2 - x] : (d2 == x));
                    ans += (d2 - d1) * f[i][d1] * (i > 2 ? g[0][i - 2][d2 - x] : (d2 == x));
                }
            for (int d2 = 0; d2 <= (i - 1) * 9; d2++)
                for (int d1 = max(x, d2 + 1); d1 <= min(d2 + x - 1, (mxb - i + 1) * 9); d1++) {
                    if (d1 - x == sl[i + 1] && x == bt[i]) ans += (d1 - d2) * g[1][i - 1][d2];
                    if (d1 - x == sl[i + 1] && x < bt[i]) ans += (d1 - d2) * g[0][i - 1][d2];
                    ans += (d1 - d2) * (i < mxb ? f[i + 1][d1 - x] : 0) * g[0][i - 1][d2];
                }
        }
    }

    return ans;
}

void solve(void) {
    int64_t l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}