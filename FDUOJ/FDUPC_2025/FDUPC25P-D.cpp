/**
 * @file FDUPC25P-D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int query(int op) {
    cout << "? " << op << endl;
    int t;
    cin >> t;
    return t;
}

void solve(void) {
    int x = 1;
    while (query(0)) x++;
    int n = 1;
    while (query(1)) n++;
    for (int i = n; i > x; i--) query(0);
    cout << "! " << n << ' ' << x << endl;
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
