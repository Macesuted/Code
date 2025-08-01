/**
 * @file 1176-1005.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    int cnt[4];
    vector<int64_t> rec[4];
    for (int i = 0; i < 4; i++) {
        cin >> cnt[i];
        rec[i].push_back(0);
        for (int t = 0, x; t < cnt[i]; t++) cin >> x, rec[i].push_back(x);
        sort(rec[i].begin() + 1, rec[i].end(), greater<int>());
        for (int t = 1; t <= cnt[i]; t++) rec[i][t] += rec[i][t - 1];
    }

    int64_t ans = 0;

    for (int c = 0; c <= min(C, cnt[2]); c++) {
        int64_t wC = rec[2][c];
        for (int d = 0; d <= min(D, cnt[3]); d++) {
            int64_t wD = rec[3][d];
            int nA = A + (C - c), nB = B + (C - c) + 2 * (D - d);
            for (int b = 0; b <= min(nB, cnt[1]); b++) {
                int64_t wB = rec[1][b];
                int64_t wA = rec[0][min(nA + 2 * (nB - b), cnt[0])];
                ans = max(ans, wA + wB + wC + wD);
            }
        }
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}