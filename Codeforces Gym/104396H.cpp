/**
 * @file 104396H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
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

int a[maxn];

void solve(void) {
    int n;
    string S, T;
    cin >> n >> S >> T;
    for (int i = 1; i <= n; i++) a[i] = (T[i - 1] - S[i - 1] + 26) % 26;
    a[0] = 0;
    for (int i = n; i >= 1; i--) a[i] = (a[i] - a[i - 1] + 26) % 26;
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += (a[i] > 0);
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