/**
 * @file arc181_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-04
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

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    bool chk = true;
    for (int i = 1; i <= n; i++) chk &= (a[i] == i);
    if (chk) return cout << 0 << endl, void();

    for (int i = 1, maxv = 0; i <= n; i++) {
        maxv = max(maxv, a[i - 1]);
        if (a[i] == i && maxv == i - 1) return cout << 1 << endl, void();
    }

    if (a[1] != n || a[n] != 1) return cout << 2 << endl, void();

    cout << 3 << endl;

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