/**
 * @file 1749A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-20
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

int cnt[2][10], x[10], y[10];

void solve(void) {
    int n, m;
    cin >> n >> m;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= m; i++) cin >> x[i] >> y[i], cnt[0][x[i]]++, cnt[1][y[i]]++;
    for (int i = 1; i <= m; i++) {
        cnt[0][x[i]]--, cnt[1][y[i]]--;
        for (int X = 1; X <= n; X++)
            for (int Y = 1; Y <= n; Y++) {
                if (X == x[i] && Y == y[i]) continue;
                cnt[0][X]++, cnt[1][Y]++;
                bool chk = true;
                for (int j = 1; j <= n; j++) chk &= (cnt[0][j] <= 1) && (cnt[1][j] <= 1);
                if (chk) return cout << "YES" << endl, void();
                cnt[0][X]--, cnt[1][Y]--;
            }
        cnt[0][x[i]]++, cnt[1][y[i]]++;
    }
    cout << "NO" << endl;
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