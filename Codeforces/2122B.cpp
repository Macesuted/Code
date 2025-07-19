/**
 * @file 2122B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-19
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

#define maxn 200005

int a[maxn], b[maxn], c[maxn], d[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        if (b[i] > d[i])
            ans += a[i] + (b[i] - d[i]);
        else if (a[i] > c[i])
            ans += a[i] - c[i];
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