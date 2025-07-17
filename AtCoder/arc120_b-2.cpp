/**
 * @file arc120_b-2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

#define maxn 505
#define mod 998244353

string a[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = ' ' + a[i];
    int64_t ans = 1;
    for (int x = 2; x <= n + m; x++) {
        map<char, int> cnt;
        for (int i = 1; i <= n; i++) {
            int j = x - i;
            if (j < 1 || j > m) continue;
            cnt[a[i][j]]++;
        }
        if (cnt['B'] && cnt['R']) return cout << 0 << endl, void();
        if (!cnt['B'] && !cnt['R']) ans = ans * 2 % mod;
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