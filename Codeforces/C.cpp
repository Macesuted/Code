/**
 * @file C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-06
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

#define maxn 600005

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] % a[i - 1] == 0) continue;
        a[i] *= ans;
        if (a[i] % a[i - 1] == 0) continue;
        int64_t v = a[i - 1] / gcd(a[i], a[i - 1]);
        a[i] *= v, ans *= v;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}