/**
 * @file 6182.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

using int128_t = __int128_t;

int128_t qpow(int128_t a, int128_t b) {
    int128_t ans = 1;
    while (b) b--, ans *= a;
    return ans;
}

void solve(void) {
    int64_t n;
    while (cin >> n) {
        int x = 1;
        while (qpow(x + 1, x + 1) <= n) x++;
        cout << x << endl;
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