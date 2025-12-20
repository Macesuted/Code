/**
 * @file 2180E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
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
    int64_t l, r;
    cin >> l >> r;

    if (l == r) return cout << 0 << endl, void();

    int b = 60;
    while ((l >> b & 1) == (r >> b & 1)) {
        int64_t t = l >> b & 1;
        l -= t << b, r -= t << b;
        b--;
    }

    int a = b;
    while (!((l & (((int64_t)1 << a) - 1)) == 0 && (r & (((int64_t)1 << a) - 1)) == ((int64_t)1 << a) - 1)) a--;

    int64_t ans = (int64_t)1 << a;
    if (((int64_t)1 << b) - l != r - ((int64_t)1 << b) + 1) return cout << ans - 1 << endl, void();

    cout << 2 * ans - 1 << endl;

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
