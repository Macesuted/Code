/**
 * @file 1174-1007.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

mt19937_64 rnd(114514);

void solve(void) {
    int n;
    cin >> n;

    map<int, uint64_t> delt;
    for (int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        uint64_t v = rnd();
        delt[l] ^= v, delt[r + 1] ^= v;
    }

    set<uint64_t> S;
    S.insert(0);
    uint64_t cur = 0;
    for (auto [x, v] : delt) S.insert(cur ^= v);

    cout << S.size() << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
