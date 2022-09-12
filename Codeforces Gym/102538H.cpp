/**
 * @file 102538H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

#define maxn 5005
#define mod 998244353

int a[maxn];
int64_t f[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    f[0] = 1;
    int64_t ans = 0;
    for (int i = 1, p1 = 0, p2 = 0; i <= 2 * n; i++)
        if (p1 < n && a[p1 + 1] == p2) {
            ans = (ans + f[1] + mod - a[++p1]) % mod;
            for (int j = 1; j <= p2; j++) f[j] = (f[j] + f[j + 1] * (j + 1) % mod * j) % mod;
        } else
            for (int j = ++p2; j; j--) f[j] = (f[j] + f[j - 1]) % mod;
    cout << ans * ((mod + 1) / 2) % mod << endl;
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