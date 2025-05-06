/**
 * @file 2107A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 105

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        int g = a[1 + (i == 1)];
        for (int j = 1; j <= n; j++)
            if (i != j) g = gcd(g, a[j]);
        if (g != a[i]) {
            ans = i;
            break;
        }
    }

    if (ans == -1) return cout << "No" << endl, void();
    cout << "Yes" << endl;
    for (int i = 1; i <= n; i++) cout << 1 + (i == ans) << ' ';
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