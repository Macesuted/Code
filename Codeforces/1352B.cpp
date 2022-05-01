/**
 * @file 1352B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
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
    if (n < k) return cout << "NO" << endl, void();
    if ((n - k) % 2 == 0) {
        cout << "YES" << endl;
        cout << n - (k - 1);
        for (int i = 2; i <= k; i++) cout << ' ' << 1;
        cout << endl;
        return;
    }
    if (n < 2 * k) return cout << "NO" << endl, void();
    if (n % 2 == 0) {
        cout << "YES" << endl;
        cout << n - (k - 1) * 2;
        for (int i = 2; i <= k; i++) cout << ' ' << 2;
        cout << endl;
        return;
    }
    cout << "NO" << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
