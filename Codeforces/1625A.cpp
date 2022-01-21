/**
 * @file 1625A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int cnt[33];

void solve(void) {
    int n, l;
    cin >> n >> l;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < l; j++, t >>= 1) cnt[j] += (t & 1);
    }
    int ans = 0;
    for (int i = l - 1; ~i; i--) ans = (ans << 1) + ((cnt[i] > n - cnt[i]) ? 1 : 0);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
