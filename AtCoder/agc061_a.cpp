/**
 * @file agc061_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-17
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

int64_t solve(int64_t n, int64_t k) {
    if (n & 1) {
        int64_t p = (k ? (solve(n - 1, k - 1) + 1) : 0);
        return p == n - 1 ? p : solve(n - 1, p);
    }
    return k ^ (((n - 1) & k) == k);
}

void solve(void) {
    int64_t n, k;
    cin >> n >> k;
    cout << solve(n, k - 1) + 1 << endl;
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