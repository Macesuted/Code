/**
 * @file 1623C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

void solve(void) {
    int n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) cout << i << endl;
        return;
    }
    if ((n & 1)) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n * k; j += n) cout << j << ' ';
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
