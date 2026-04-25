/**
 * @file 1228A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int l, r;
    cin >> l >> r;

    for (int i = l; i <= r; i++) {
        int v = i, cnt = 0;
        unordered_set<int> digits;
        while (v) digits.insert(v % 10), v /= 10, cnt++;
        if ((int)digits.size() == cnt) return cout << i << endl, void();
    }

    cout << -1 << endl;

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
