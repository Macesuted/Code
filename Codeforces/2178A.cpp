/**
 * @file 2178A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-27
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
    string s;
    cin >> s;

    int cntN = 0;
    for (auto c : s) cntN += (c == 'N');

    int cntY = s.size() - cntN;

    cout << (cntY <= 1 ? "YES" : "NO") << endl;

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
