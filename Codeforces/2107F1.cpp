/**
 * @file 2107F1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 5005

int a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> b[i];

    int64_t ans = INT64_MAX;
    for (int x = 1; x <= n; x++) {
        for (int i = 1; i <= n; i++) a[i] = b[i];
        int64_t cur = 0;
        if (x < n) swap(a[x], a[n]), cur += n - x;
        cur += a[n];
        for (int i = n - 1; i; i--) {
            if (a[i] > a[i + 1]) cur++, swap(a[i], a[i + 1]);
            cur += a[i];
        }
        ans = min(ans, cur);
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