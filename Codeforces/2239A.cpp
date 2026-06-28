/**
 * @file 2239A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
#define mod 998244353

int a[maxn];

int64_t solve(void) {
    int n, xsum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], xsum ^= a[i];

    if (n == 1) return 0;
    if (!xsum) return 1;

    int ans = 0;

    for (int i = 1; i <= n; i++)
        if ((xsum ^ a[i]) < a[i]) ans++;

    return ans;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) cout << solve() << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
