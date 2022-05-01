/**
 * @file 3948.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define mod 998244353

int a[maxn];

void solve(void) {
    int n, t = INT_MAX;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], t = min(t, a[i] & -a[i]);
    int minVal = INT_MAX;
    for (int i = 1; i <= n; i++)
        if ((a[i] & -a[i]) == t) minVal = min(minVal, a[i] / t);
    cout << minVal / 2 + 1 << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("nim.in", "r", stdin), freopen("nim.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
