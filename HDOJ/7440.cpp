/**
 * @file 7440.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[2];

void solve(void) {
    int n, k;
    cin >> n >> k;
    int64_t ans = 1;
    for (int i = 0; i < k; i++) ans *= cnt[n >> i & 1];
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cnt[0] = cnt[1] = 0;
    for (int a = 0; a < 2; a++)
        for (int b = 0; b < 2; b++)
            for (int c = 0; c < 2; c++)
                for (int d = 0; d < 2; d++) cnt[((a & b) ^ c) | d]++;

    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}