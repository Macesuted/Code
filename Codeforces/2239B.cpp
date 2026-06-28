/**
 * @file 2239B.cpp
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

#define maxn 200005

int a[maxn];
int64_t f[maxn];

void solve(void) {
    int n, d;
    cin >> n >> d;
    f[0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], f[i] = f[i - 1] + a[i];

    auto getSum = [&](int l, int r) -> int64_t { return f[r] - f[l - 1]; };

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = i - d, r = i + d;
        int64_t cur = -a[i];
        if (l <= 0) cur += getSum(n + l, n), l = 1;
        if (r > n) cur += getSum(1, r - n), r = n;
        cur += getSum(l, r);
        ans += max((int64_t)0, (int64_t)a[i] * 2 * d - cur);
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
