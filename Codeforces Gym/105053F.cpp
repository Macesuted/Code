/**
 * @file 105053F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
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

int a[maxn], b[maxn], cnt[maxn], g[maxn];
bool f[maxn];

void solve(void) {
    int n, sum = 0;
    cin >> n;
    int delt = 0;
    bool zero = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i], sum += a[i], zero |= !a[i], delt = gcd(delt, b[i]);
        if (i > 1) cnt[a[i]]++;
    }
    f[0] = true;
    for (int t = 1; t < maxn; t++) {
        if (!cnt[t]) continue;
        for (int i = 0; i <= sum; i++) g[i] = 0;
        for (int i = 0; i <= sum; i++) {
            if (f[i]) g[i] = cnt[t] + 1;
            if (i >= t) g[i] = max(g[i], g[i - t] - 1);
            f[i] |= g[i];
        }
    }
    f[0] = zero;
    for (int i = 0; i <= sum; i++)
        if (f[i] && i % delt == (sum - i) % delt) return cout << 'Y' << endl, void();
    cout << 'N' << endl;
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