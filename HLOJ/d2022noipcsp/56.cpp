/**
 * @file 56.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 18

int a[maxn], f[1 << maxn];

void solve(void) {
    int n, cnt = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, greater<int>());
    while (n && a[n - 1] == 1) n--, cnt++;
    if (cnt > 1) return cout << "Poor hzwer!" << endl, void();
    memset(f, 0x3f, sizeof(f)), f[0] = cnt;
    for (int S = 0; S < (1 << n); S++)
        for (int i = 0; i < n; i++)
            if (!(S >> i & 1))
                f[S | (1 << i)] = min(f[S | (1 << i)], f[S] + max(1, f[S] / (a[i] - 1) + (f[S] % (a[i] - 1) > 0)));
    cout << f[(1 << n) - 1] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("flower.in", "r", stdin), freopen("flower.out", "w", stdout);
#endif
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