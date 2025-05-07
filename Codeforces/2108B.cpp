/**
 * @file 2108B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-07
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

void solve(void) {
    int n, x;
    cin >> n >> x;
    if (x == 0) {
        if (n == 1) return cout << -1 << endl, void();
        if (n % 2 == 0) return cout << n << endl, void();
        return cout << n + 3 << endl, void();
    }
    if (x == 1) {
        if (n % 2 == 0) return cout << n + 3 << endl, void();
        return cout << n << endl, void();
    }
    int b = min(n, __builtin_popcount(x));
    if (b > 1 && (n - b) % 2 == 1) b--;
    cout << n - b + x + ((n - b) % 2 == 1) << endl;
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