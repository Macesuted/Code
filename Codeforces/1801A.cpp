/**
 * @file 1801A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-09
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
    cin >> n >> m;
    cout << n * m << endl;
    int b = 1;
    while (b < m) b <<= 1;
    for (int i = 1; i <= n; i++) {
        int c = (i - 1) * b;
        for (int j = 1; j <= m; j++) cout << c++ << ' ';
        cout << endl;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}