/**
 * @file 1998A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
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

void solve(void) {
    int x, y, n;
    cin >> x >> y >> n;
    if (n & 1) cout << x << ' ' << y << endl, n--;
    for (int i = 1; i * 2 <= n; i++) cout << x << ' ' << y + i << endl << x << ' ' << y - i << endl;
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