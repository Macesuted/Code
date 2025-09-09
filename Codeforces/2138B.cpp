/**
 * @file 2138B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-08
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

#define maxn 500005

int a[maxn], p[maxn], l[maxn], r[maxn], lim[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i, lim[i] = n + 1;

    set<int> S;
    S.insert(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = p[i];
        S.insert(x);
        r[x] = *S.upper_bound(x);
    }

    S.clear(), S.insert(0);
    for (int i = n; i >= 1; i--) {
        int x = p[i];
        S.insert(x);
        l[x] = *prev(S.find(x));
    }

    for (int i = 1; i <= n; i++)
        if (l[i]) lim[l[i]] = min(lim[l[i]], r[i]);

    for (int i = n - 1; i >= 1; i--) lim[i] = min(lim[i], lim[i + 1]);

    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, cout << (r < lim[l] ? "YES" : "NO") << endl;

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