/**
 * @file 100200F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
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

#define maxn 400005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], a[n + i] = a[i];
    for (int i = 1; i <= 2 * n; i++) a[i] += a[i - 1];

    map<int, int> S;
    int ans = 0;
    for (int i = 0; i < n; i++) S[a[i]]++;
    for (int i = 1; i <= n; i++) {
        S[a[i - 1]]--, S[a[i + n - 1]]++;
        while (!S.begin()->second) S.erase(S.begin());
        ans += (a[i - 1] < S.begin()->first);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("positive.in", "r", stdin), freopen("positive.out", "w", stdout);
#endif
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