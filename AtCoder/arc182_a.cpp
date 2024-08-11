/**
 * @file arc182_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 5005
#define mod 998244353

typedef pair<int, int> pii;

pii a[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i].first >> a[i].second;
    int64_t ans = 1;
    for (int i = 1; i <= m; i++) {
        int cntl = 0, cntr = 0;
        for (int j = 1; j <= m; j++)
            if ((j < i && a[j].second > a[i].second) || (j > i && a[j].second < a[i].second)) {
                if (a[j].first <= a[i].first) cntl++;
                if (a[j].first >= a[i].first) cntr++;
            }
        if (cntl && cntr) return cout << 0 << endl, void();
        if (!cntl && !cntr) ans = ans * 2 % mod;
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
    // cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}