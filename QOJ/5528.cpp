/**
 * @file 5528.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, m;
    cin >> n, m = n;
    auto norm = [&](int p) { return (p - 1 + n) % n + 1; };
    if (!(n & 1)) n--;
    for (int i = 1; i <= n; i++) {
        if (!(m & 1)) cout << i << ' ' << m << endl;
        for (int t = 1; t <= n / 2; t++) {
            int x = norm(i - t), y = norm(i + t);
            cout << min(x, y) << ' ' << max(x, y) << endl;
        }
    }
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