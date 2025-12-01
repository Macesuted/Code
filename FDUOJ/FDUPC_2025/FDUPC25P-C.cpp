/**
 * @file FDUPC25P-C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-27
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

#define maxn 100005

int a[maxn], x[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, u, v; i <= n; i++) cin >> u >> v, a[i] = v - u;
    for (int i = 1; i <= n; i++) cin >> x[i];

    sort(a + 1, a + n + 1), sort(x + 1, x + n + 1);

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += abs(a[i] - x[i]);
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
