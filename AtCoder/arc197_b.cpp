/**
 * @file arc197_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-04
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

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;

    int64_t sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    sort(a + 1, a + n + 1);

    int ans = 0;
    for (int i = n, p = n; i > 1; sum -= a[i--]) {
        while (a[p] * i > sum) p--;
        ans = max(ans, i - p);
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