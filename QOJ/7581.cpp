/**
 * @file 7581.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005
#define maxv 1005

int cnt[4][maxv][maxv];

int64_t C3(int n) { return (int64_t)n * (n - 1) * (n - 2) / 6; }

void solve(void) {
    int n;
    cin >> n;

    memset(cnt, 0, sizeof(cnt));

    auto add = [&](int t, int xl, int xr, int yl, int yr) {
        if (xl > xr || yl > yr) return;
        cnt[t][xl][yl]++, cnt[t][xl][yr + 1]--;
        cnt[t][xr + 1][yl]--, cnt[t][xr + 1][yr + 1]++;
        return;
    };

    for (int i = 1, xl, yl, xr, yr; i <= n; i++) {
        cin >> xl >> yl >> xr >> yr;
        add(0, xl, xr, yl, yr);
        add(1, xl, xr - 1, yl, yr);
        add(2, xl, xr, yl, yr - 1);
        add(3, xl, xr - 1, yl, yr - 1);
    }

    __int128_t ans = 0;
    for (int t = 0; t < 4; t++) {
        for (int i = 1; i <= 1000; i++)
            for (int j = 2; j <= 1000; j++) cnt[t][i][j] += cnt[t][i][j - 1];
        for (int i = 2; i <= 1000; i++)
            for (int j = 1; j <= 1000; j++) cnt[t][i][j] += cnt[t][i - 1][j];
    }

    for (int t = 0; t < 4; t++)
        for (int i = 1; i <= 1000; i++)
            for (int j = 1; j <= 1000; j++) ans += C3(cnt[t][i][j]) * (t == 0 || t == 3 ? +1 : -1);

    cout << (int64_t)ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
