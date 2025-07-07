/**
 * @file E.cpp
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

/*
L < x + R
L >= R - x

R <= L + x < R + 2x

delta = L + x - R

0 <= delta / 2 < x

L < delt / 2
L + R < x

*/

#define maxn 50005

int64_t a[maxn], sum[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];

    if (sum[n] % 2 == 1) return cout << -1 << endl, void();

    int p = 0;
    while (sum[p] < sum[n] - sum[p]) p++;
    int64_t delt = sum[p] - (sum[n] - sum[p]);

    if (delt == 0) {
        cout << 1 << endl;
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << endl;
        return;
    }

    int64_t x = delt / 2;
    if (sum[p - 1] < x) return cout << -1 << endl, void();

    cout << 2 << endl;
    for (int i = 1; i <= p - 1; i++) {
        int64_t v = min(a[i], x);
        a[i] -= v, x -= v, cout << v << ' ';
    }
    a[p] -= delt / 2, cout << delt / 2 << ' ';
    for (int i = p + 1; i <= n; i++) cout << 0 << ' ';
    cout << endl;

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << endl;

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