/**
 * @file 101808F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

#define mod 7901
#define maxn 1005

int cnt[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = 1;
    for (int i = 1; i < maxn; i++) cnt[i] = 0;
    for (int i = 1, v; i <= n; i++) cin >> v, ans = ans * ++cnt[v] % mod;
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