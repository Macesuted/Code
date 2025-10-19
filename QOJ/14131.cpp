/**
 * @file 14131.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-11
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

using pii = pair<int, int>;

int64_t f[2][6][505];

void solve(void) {
    int n, K;
    cin >> n >> K;

    vector<pii> A[2];
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (x <= 100)
            A[0].emplace_back(x, y);
        else
            A[1].emplace_back(y, x);
    }

    for (int t = 0; t < 2; t++) {
        for (int j = 0; j <= K; j++)
            for (int k = 0; k <= 100 * j; k++) f[t][j][k] = -1;
        f[t][0][0] = 0;
        for (auto [x, y] : A[t])
            for (int j = K - 1; ~j; j--)
                for (int k = 0; k <= 100 * j; k++)
                    if (f[t][j][k] != -1) f[t][j + 1][k + x] = max(f[t][j + 1][k + x], f[t][j][k] + y);
    }

    int64_t ans = 0;

    for (int l = 0, r = K; l <= K; l++, r--)
        for (int vl = 0; vl <= 100 * l; vl++)
            for (int vr = 0; vr <= 100 * r; vr++)
                if (f[0][l][vl] != -1 && f[1][r][vr] != -1) ans = max(ans, (vl + f[1][r][vr]) * (f[0][l][vl] + vr));

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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}